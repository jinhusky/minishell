/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:59:06 by jhor              #+#    #+#             */
/*   Updated: 2026/02/23 23:27:36 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*merge_env_list(char *str, t_envp *env_ls)
{
	str = NULL;
	str = ft_strdup(env_ls->key);
	str = ft_strjoin_free(str, ft_strdup("="));
	str = ft_strjoin_free(str, ft_strdup(env_ls->value));
	return (str);
}

char	**build_array_list(t_shell *envp, t_globe *p)
{
	t_envp	*ptr;
	int		i;
	char	**array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(char *) * (envp->size + 1));
	ptr = envp->head;
	while (ptr)
	{
		array[i] = merge_env_list(array[i], ptr);
		ptr = ptr->next;
		i++;
	}
	array[envp->size] = NULL;
	return (array);
}

int	compare_two_index(char **indx1, char **indx2, t_globe *p)
{
	int		i;
	char	*tmp;
	int		swap;

	tmp = NULL;
	swap = 0;
	if (ft_strncmp(*indx1, *indx2, ft_strlen(*indx1)) > 0)
	{
		tmp = *indx1;
		*indx1 = *indx2;
		*indx2 = tmp;
		swap = 1;
	}
	return (swap);
}

char	**bubble_sort_alpha(char **array, t_globe *p)
{
	int	swap;
	int	i;

	swap = 1;
	while (swap)
	{
		swap = 0;
		i = 0;
		while (i < p->envp_ls->size - 1)
		{
			if (compare_two_index(&array[i], &array[i + 1], p))
				swap = 1;
			i++;
		}
	}
	return (array);
}

void	free_array_list(char **array, t_globe *p)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
