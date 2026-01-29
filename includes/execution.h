/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:14:42 by kationg           #+#    #+#             */
/*   Updated: 2026/01/29 22:29:17 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

void	execute(t_ast *root, t_globe *p);
int	apply_redirections(t_ast *cmd);
char **build_envp_array(t_shell envp_ls);
bool is_builtin(char *cmd);
char	*envp_value(char *k, char *v, t_shell *envp);
void	set_envp(char **envp, t_shell *shell);
void	free_envp_ls(t_shell *shell);
void	set_exit_code(int status, t_globe *p);
void	signal_handler(int signal);
void	heredoc_signal_handler(int signal);
void	signal_get_code(int signa, t_globe *p);






#endif

