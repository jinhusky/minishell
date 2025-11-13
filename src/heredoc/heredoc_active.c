/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_active.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:01:33 by jhor              #+#    #+#             */
/*   Updated: 2025/11/13 16:42:12 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//TODO create a function to traverse the AST tree and mark tokens with quotes
//TODO work out on how to implement heredoc.
//! retain the quotes after expansion to avoid unnecessary splitting and wrong semantic interpretation
//! heredoc delimiter with quotes does not expand, without it it expands.

void	init_read_content(char **lns, char **rslt, int *ttl_len, int *line_len)
{
	*lns = NULL;
	*rslt = NULL;
	*ttl_len = 0;
	*line_len = 0;
}

char	*read_content(char *delimiter)
{
	char	*lines;
	char	*result;
	int		total_len;
	int		line_len;
	
	init_read_content(&lines, &result, &total_len, &line_len);
	while (1)
	{
		lines = readline("> ");
		// printf("readline: %s$\n", lines);
		if (!lines)
			break;
		if (ft_strncmp(lines, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(lines);
			break;
		}
		line_len = ft_strlen(lines);
		// printf("*before memcopy* result: %s$\n", result);
		result = realloc(result, total_len + line_len + 2);
		ft_memcpy(result + total_len, lines, line_len);
		total_len = total_len + line_len;
		result[total_len++] = '\n';
		result[total_len] = '\0';
		// printf("*after memcopy* result: %s$\n", result);
		free(lines);
	}
	return (result);
}

void	find_heredoc(t_ast *child, t_parser *p)
{
	int		i;
	char	*line;
	t_ast	*heredoc;
	// char tmp[256] = " ";

	i = 0;
	line = NULL;
	heredoc = NULL;
	while (i < child->childcount && child->children[i])
	{
		if (child->children[i]->type == AST_HEREDOC)
		{
			heredoc = child->children[i];
			pipe(heredoc->heredoc_fd);
			strip_quotes(heredoc->children[0]->token_ref->lexeme, p);
			line = read_content(heredoc->children[0]->token_ref->lexeme);
			// printf("%s", line);
			if (!line)
				write(heredoc->heredoc_fd[1], "", 1);
			else
				write(heredoc->heredoc_fd[1], line, ft_strlen(line));
			close(heredoc->heredoc_fd[1]);
			// read(heredoc->heredoc_fd[0], tmp, 256);
			// printf("tmp:%s$", tmp);
			free(line);
		}
		// printf("---NEXT-ITERATION---\n\n");
		i++;
	}
}

void	ast_loop(t_ast *root, t_parser *p)
{
	int		i = 0;
	t_ast	*cur_cmd;
	
	cur_cmd = NULL;
	if (root->children)
	{
		while (i < root->childcount && root->children[i])
		{
			cur_cmd = root->children[i];
			find_heredoc(cur_cmd, p);
			i++;
		}
	}
}