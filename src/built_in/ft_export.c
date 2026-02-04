/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:25:55 by kationg           #+#    #+#             */
/*   Updated: 2026/02/04 22:06:41 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include <cstdlib.h>

//first char of a env var must be alpha or _
static bool	valid_env_var(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (false);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	set_env_var(char *arg, t_globe *p)
{
	char	*eq_pos;
	t_envp	*tmp;
	t_envp	*ptr;

	ptr = p->envp_ls->head;
	eq_pos = ft_strchr(arg, '=');
	tmp = (t_envp *)malloc(sizeof(t_envp));
	tmp->next = NULL;
	tmp->key = ft_substr(arg, 0, eq_pos - arg);
	tmp->value = ft_substr(eq_pos, 1, ft_strlen(arg));
	while (ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = tmp;
	p->envp_ls->size++;
	return ;
}

int	ft_export(char **argv, t_globe *p)
{
	int		i;
	char	*value;

	i = 0;
	if (!argv[1])
		return (print_export(p), 0);
	while (argv[i])
	{
		if (!valid_env_var(argv[i]))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
			return (EXIT_FAILURE);
		}
		if (ft_strchr(argv[i], '='))
		{
			if ((value = envp_value(argv[i], NULL, p->envp_ls)))
			{
				ft_printf("value:%s\n", value);
				ft_printf("i am in here\n");
				envp_value(argv[i], argv[i], p->envp_ls);
			}
			else
				set_env_var(argv[i], p);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
