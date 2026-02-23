/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:14:42 by kationg           #+#    #+#             */
/*   Updated: 2026/02/24 01:23:07 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/stat.h>
# include <linux/limits.h>
# include <sys/wait.h>
# include "../minishell.h"

void		execute(t_ast *root, t_globe *p);
int			execute_pipeline(t_ast *root, t_globe *p);
void		print_redir_err(t_ast *redir);
int			apply_redirections(t_ast *cmd);
char		**build_envp_array(t_shell envp_ls);
bool		is_builtin(char *cmd);
int			key_equals(const char *a, const char *b);
char		*envp_value(char *k, char *v, t_shell *envp);
void		set_envp_array(char **envp, t_shell **shell, t_globe *p);
void		free_envp_ls(t_shell *shell);
void		set_exit_code(int status, t_globe *p);
void		signal_handler(int signal);
void		heredoc_signal_handler(int signal);
char		*read_content(char *delimiter, t_globe *p);
void		readline_prep(char *lexeme, int rpipe, int wpipe, t_globe *p);
void		read_into_pipe(char *lexeme, int wpipe, t_globe *p);
void		signal_get_code(int signa, t_globe *p);
int			run_builtin(t_globe *p, char **argv, int in_parent);
void		set_hd_exit_code(int status, t_globe *p);
void		free_strv(char **v);
void		child_execute_cmd(t_ast *cmd, t_globe *p, int in_fd, int out_fd);
void		exec_external(t_globe *p, char **argv);
int			run_single_cmd_in_parent(t_ast *cmd, t_globe *p);
void		process_err_msg(char *arg, t_globe *p);
void		find_heredoc(t_ast *child, t_globe *p);

#endif
