/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:25:55 by kationg           #+#    #+#             */
/*   Updated: 2026/02/23 23:22:38 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	print_error_export(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`%s': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
}

void	print_export(t_globe *p)
{
	int		i;
	char	**array;

	i = 0;
	array = NULL;
	array = build_array_list(p->envp_ls, p);
	array = bubble_sort_alpha(array, p);
	while (array[i])
	{
		ft_printf("declare -x %s\n", array[i]);
		i++;
	}
	free_array_list(array, p);
}

int	ft_export(char **argv, t_globe *p)
{
	int		i;

	i = 0;
	if (!argv[1])
		return (print_export(p), 0);
	while (argv[i])
	{
		if (!valid_env_var(argv[i]))
		{
			print_error_export(argv[i]);
			return (EXIT_FAILURE);
		}
		if (ft_strchr(argv[i], '='))
		{
			if ((export_envp_value(argv[i], NULL, p->envp_ls)))
				export_envp_value(argv[i], argv[i], p->envp_ls);
			else
				set_env_var(argv[i], p);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
