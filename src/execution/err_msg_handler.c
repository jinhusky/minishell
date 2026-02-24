/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:13:44 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 17:03:52 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_err_mssg(char *cmd, char *err_mssg)
{
	char	*str;

	str = strdup("minishell: ");
	if (cmd)
	{
		str = ft_strjoin_free(str, ft_strdup(cmd));
		str = ft_strjoin_free(str, ft_strdup(": "));
	}
	str = ft_strjoin_free(str, ft_strdup(err_mssg));
	ft_putendl_fd(str, 2);
	free(str);
	return ;
}

void	remove_dot_slash(char *arg, char **raw)
{
	*raw = ft_substr(arg, 2, (ft_strlen(arg) - 2 + 1));
	return ;
}

bool	slash_exist(char *arg)
{
	if (ft_strchr(arg, '/'))
		return (true);
	return (false);
}

int	process_fdir(char *arg)
{
	char		*raw;
	struct stat	statbuf;

	if (stat(arg, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			print_err_mssg(arg, "Is a directory");
			return (126);
		}
		else if (S_ISREG(statbuf.st_mode))
		{
			if (arg[0] == '.' && arg[1] == '/')
				remove_dot_slash(arg, &raw);
			if (open(raw, O_RDONLY | O_WRONLY) == -1)
				print_err_mssg(arg, "Permission denied");
			free(raw);
			return (126);
		}
	}
	else
		print_err_mssg(arg, "No such file or directory");
	return (127);
}

void	process_err_msg(char *arg, t_globe *p)
{
	int	errnum;

	errnum = 0;
	if (slash_exist(arg))
	{
		errnum = process_fdir(arg);
		p->exit_code[0] = errnum;
		return ;
	}
	else
	{
		if (!envp_value("PATH", NULL, p->envp_ls))
			print_err_mssg(arg, "No such file or directory");
		else
			print_err_mssg(arg, "Command not found");
	}
	p->exit_code[0] = 127;
	return ;
}
