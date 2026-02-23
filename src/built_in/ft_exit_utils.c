/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:09:27 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 23:12:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	invalid_numeric_msg(char *arg, t_globe *p)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	p->exit_code[0] = 2;
}
