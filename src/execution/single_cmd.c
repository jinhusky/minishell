/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:20:04 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 00:46:34 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	failed_status(int status, int svd_in, int svd_out, t_globe *p)
{
	if (status != 0)
	{
		status = 1;
		dup2(svd_in, STDIN_FILENO);
		dup2(svd_out, STDOUT_FILENO);
		close(svd_in);
		close(svd_out);
		p->exit_code[0] = status;
		return (true);
	}
	return (false);
}

int	run_single_cmd_in_parent(t_ast *cmd, t_globe *p)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in < 0 || saved_out < 0)
	{
		p->exit_code[0] = 1;
		return (1);
	}
	status = apply_redirections(cmd);
	if (failed_status(status, saved_in, saved_out, p))
		return (status);
	else if (!cmd->argv || !cmd->argv[0])
		status = 0;
	else
		status = run_builtin(p, cmd->argv, 1);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	p->exit_code[0] = status;
	return (status);
}
