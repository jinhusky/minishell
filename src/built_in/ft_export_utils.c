/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:59:06 by jhor              #+#    #+#             */
/*   Updated: 2026/02/04 16:58:26 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//build array of env list



char	*merge_env_list(char *str, t_envp *env_ls)
{
	str = NULL;
	str = ft_strdup(env_ls->key);
	str = ft_strjoin_free(str, ft_strdup("="));
	str = ft_strjoin_free(str, ft_strdup(env_ls->value));
	return (str);
}

static char **build_array_list(t_shell *envp, t_globe *p)
{
	t_envp	*ptr;
	int		i;
	char	**array;

	i = 0;
	array = NULL;
	array = malloc(sizeof(char *) * (envp->size + 1));
	ptr = envp->head;
	while(ptr)
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

static char	**bubble_sort_alpha(char **array, t_globe *p)
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

//check the cmd is single then run singly (declare -x and print sorted env list)
//check the cmd is more than one, then it should include the arguments into the env list.
//format has to be alpha or _ at the start and alphanum for the rest of the characters.

//int	ft_export(char **argv, t_globe *p)
//{
//	char	**array;
//	int		i;

//	array = NULL;
//	i = 0;
//	if (argv[0] && !argv[1])
//	{
//		print_export(p);
//	}
//	else
//	{
//		while (argv[++i])
//		{
//			if (export_error(argv[i]))
//			{
//				error_export_msg(argv[i]);
//				return (p->exit_code[0] = 1, 1);
//			}
//			else
//				run_export(argv[i], p);
//		}
//	}
//	return (0);
//}
