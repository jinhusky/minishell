/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:00:33 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:00:42 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_redir_err(t_ast *redir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir->token_ref->lexeme, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}
