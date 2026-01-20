/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 05:14:42 by kationg           #+#    #+#             */
/*   Updated: 2026/01/20 09:47:26 by kationg          ###   ########.fr       */
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





#endif

