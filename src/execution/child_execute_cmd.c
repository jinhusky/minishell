/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:11:44 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:12:00 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_execute_cmd(t_ast *cmd, t_globe *p, int in_fd, int out_fd)
{
	int	status;

	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	status = apply_redirections(cmd);
	if (status != 0)
		exit(status);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exit(run_builtin(p, cmd->argv, 0));
	exec_external(p, cmd->argv);
}
