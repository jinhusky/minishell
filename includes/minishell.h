/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:56:07 by kationg           #+#    #+#             */
/*   Updated: 2025/09/20 19:09:35 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../Libft/libft.h"
#include <stdbool.h>

typedef struct s_envp
{
	char *key;
	char *value;
	struct s_envp *next;
}   t_envp;

typedef struct shell
{
    t_envp *head;
} t_shell;

int ft_echo(char **argv);

void    ft_pwd(void);


void get_envp(char **envp, t_shell *env);
#endif
