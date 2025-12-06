/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peeps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 08:53:31 by kationg           #+#    #+#             */
/*   Updated: 2025/12/03 12:38:10 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **build_argv_array(t_ast *cmd)
{
    int     i;
    int     argc;
    char  **argv;

    if (!cmd || cmd->type != AST_COMMAND)
        return (NULL);

    argc = 0;
    i = 0;
    while (i < cmd->childcount)
    {
        if (cmd->children[i]->type == AST_WORD
            || cmd->children[i]->type == AST_ARGUMENT)
            argc++;
        i++;
    }

    argv = (char **)ft_calloc(argc + 1, sizeof(char *));
    if (!argv)
        return (NULL);

    i = 0;
    int j = 0;
    while (i < cmd->childcount)
    {
        t_ast *child = cmd->children[i];
        char  *arg = NULL;

        if (child->type == AST_WORD)
            arg = child->token_ref->lexeme;
        else if (child->type == AST_ARGUMENT && child->childcount > 0)
            arg = child->children[0]->token_ref->lexeme;

        if (arg)
        {
            argv[j] = ft_strdup(arg);
            j++;
        }
        i++;
    }
    argv[j] = NULL;
    return (argv);
}

char **build_envp_array(t_shell shell)
{
    t_envp  *ptr;
    char   **res;
    int      i;

    ptr = shell.envp_head;
    res = (char **)ft_calloc(shell.size + 1, sizeof(char *));
    if (!res)
        return (NULL);
    i = 0;
    while (ptr)
    {
        char *tmp;

        tmp = ft_strdup(ptr->key);          
        tmp = ft_strjoin(tmp, "=");         
        tmp = ft_strjoin(tmp, ptr->value);

        res[i] = tmp;
        ptr = ptr->next;
        i++;
    }
    res[i] = NULL;
    return (res);
}

void execute(char **envp_exec, char **argv, t_shell *shell)
{
    char   *path_env;
    char  **paths;
    int     i;
    char   *fullpath;

    if (!argv || !argv[0])
		//need to replace with exit code(error)
        return;

    if (ft_strchr(argv[0], '/'))
        execve(argv[0], argv, envp_exec);

    path_env = envp_value("PATH", NULL, *shell);
    if (!path_env)
        execve(argv[0], argv, envp_exec);

    paths = ft_split(path_env, ':');
    if (!paths)
        execve(argv[0], argv, envp_exec);

    i = 0;
    while (paths[i])
    {
        fullpath = ft_strdup(paths[i]);
        fullpath = ft_strjoin(fullpath, "/");
        fullpath = ft_strjoin(fullpath, argv[0]);

        if (access(fullpath, X_OK) == 0)
        {
            execve(fullpath, argv, envp_exec);
            perror("execve");
            _exit(127);
        }
        free(fullpath);
        i++;
    }
    
}

static int	match_delimiter(char *line, char *deli)
{
    size_t len_line;
    size_t len_deli;

    if (!line)
        return (0);
    len_line = ft_strlen(line);
    len_deli = ft_strlen(deli);
    if (len_line != len_deli)
        return (1);
    if (ft_strncmp(line, deli, len_deli) == 0)
        return (0);
    return (1);
}

void	prep_heredoc(t_ast *node)
{
    char	*deli;
    char	*line;

    if (!node || node->type != AST_HEREDOC)
        return;
    deli = node->children[0]->token_ref->lexeme;
    if (pipe(node->heredoc_fd) == -1)
    {
        perror("pipe");
        return;
    }
    line = readline("heredoc> ");
    while (match_delimiter(line, deli))
    {
        if (!line)
            break;
        write(node->heredoc_fd[1], line, ft_strlen(line));
        write(node->heredoc_fd[1], "\n", 1);
        free(line);
        line = readline("heredoc> ");
    }
    if (line)
        free(line);
    close(node->heredoc_fd[1]);
}

void	redirection(t_ast *node)
{
    int	new_fd;

    if (!node)
        return;

    if (node->type == AST_REDIR_IN)
    {
        new_fd = open(node->children[0]->token_ref->lexeme, O_RDONLY);
        if (new_fd == -1)
        {
            perror("open");
            _exit(1);
        }
        dup2(new_fd, STDIN_FILENO);
        close(new_fd);
    }
    else if (node->type == AST_REDIR_OUT)
    {
        new_fd = open(node->children[0]->token_ref->lexeme,
                      O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (new_fd == -1)
        {
            perror("open");
            _exit(1);
        }
        dup2(new_fd, STDOUT_FILENO);
        close(new_fd);
    }
    else if (node->type == AST_APPEND)
    {
        new_fd = open(node->children[0]->token_ref->lexeme,
                      O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (new_fd == -1)
        {
            perror("open");
            _exit(1);
        }
        dup2(new_fd, STDOUT_FILENO);
        close(new_fd);
    }
    else if (node->type == AST_HEREDOC)
    {
        dup2(node->heredoc_fd[0], STDIN_FILENO);
        close(node->heredoc_fd[0]);
    }
}

void	walk_ast_child(t_ast *node)
{
    int i;

    if (!node)
        return;
    redirection(node);
    i = 0;
    while (i < node->childcount)
    {
        walk_ast_child(node->children[i]);
        i++;
    }
}

void	find_cmd_num(t_ast *node, int *cmd_count)
{
    if (node->type == AST_COMMAND)
        (*cmd_count)++;
}

void	walk_ast_parent(t_ast *node, int *cmd_count)
{
    int i;

    if (!node)
        return;
    find_cmd_num(node, cmd_count);
    prep_heredoc(node);
    i = 0;
    while (i < node->childcount)
    {
        walk_ast_parent(node->children[i], cmd_count);
        i++;
    }
}

void collect_commands(t_ast *node, t_ast **cmds, int *idx)
{
    int i;

    if (!node)
        return;
    if (node->type == AST_COMMAND)
    {
        cmds[*idx] = node;
        (*idx)++;
    }
    i = 0;
    while (i < node->childcount)
    {
        collect_commands(node->children[i], cmds, idx);
        i++;
    }
}

void execute_pipeline(t_ast *root, t_shell *shell)
{
    int     cmd_count;
    int     i;
    int   **pipes;
    pid_t  *pids;
    t_ast **cmds;
    char  **envp_exec;

    if (!root)
        return;

    cmd_count = 0;
    walk_ast_parent(root, &cmd_count);
    if (cmd_count == 0)
        return;

    cmds = (t_ast **)malloc(sizeof(t_ast *) * cmd_count);
    if (!cmds)
        return;
    int idx = 0;
    collect_commands(root, cmds, &idx);

    pipes = NULL;
    if (cmd_count > 1)
    {
        pipes = (int **)malloc(sizeof(int *) * (cmd_count - 1));
        if (!pipes)
        {
            free(cmds);
            return;
        }
        i = 0;
        while (i < cmd_count - 1)
        {
            pipes[i] = (int *)malloc(sizeof(int) * 2);
            if (!pipes[i] || pipe(pipes[i]) == -1)
            {
                perror("Error when creating pipes");
				// free got bug
            }
            i++;
        }
    }

    pids = (pid_t *)malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
    {
        return;
    }
    envp_exec = build_envp_array(*shell);
    i = 0;
    while (i < cmd_count)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            if (cmd_count > 1)
            {
                if (i > 0)
                    dup2(pipes[i - 1][0], STDIN_FILENO);
                if (i < cmd_count - 1)
                    dup2(pipes[i][1], STDOUT_FILENO);

                int k = 0;
                while (k < cmd_count - 1)
                {
                    close(pipes[k][0]);
                    close(pipes[k][1]);
                    k++;
                }
            }
            walk_ast_child(cmds[i]);
            char **argv = build_argv_array(cmds[i]);
            execute(envp_exec, argv, shell);
        }
        else
        {
            pids[i] = pid;
        }
        i++;
    }
    if (cmd_count > 1)
    {
        int k = 0;
        while (k < cmd_count - 1)
        {
            close(pipes[k][0]);
            close(pipes[k][1]);
            k++;
        }
    }
    i = 0;
    while (i < cmd_count)
    {
        int status;
        waitpid(pids[i], &status, 0);
        i++;
    }
    free(pids);
    free(cmds);
    if (pipes)
    {
        int k = 0;
        while (k < cmd_count - 1)
        {
            free(pipes[k]);
            k++;
        }
        free(pipes);
    }
    if (envp_exec)
    {
        int k = 0;
        while (envp_exec[k])
        {
            free(envp_exec[k]);
            k++;
        }
        free(envp_exec);
    }
}

