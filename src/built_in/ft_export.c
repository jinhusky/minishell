/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:35:12 by kationg           #+#    #+#             */
/*   Updated: 2026/01/19 09:25:31 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export(char **args, t_shell *envp_lst)
{
	//if there is no assignment (=) then we should not handle
	if (!ft_strchr(args[1], '='))
		return;
	//we only handle create new env var or edit env var value
	char	**split = ft_split(args[1], '=');
	envp_value(split[0], split[1], envp_lst, args[1]);
}
