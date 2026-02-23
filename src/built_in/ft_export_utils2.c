/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:54:37 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:19:52 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_key(char *eq_pos, char *k)
{
	char	*pinpoint;

	pinpoint = ft_strchr(k, '=');
	eq_pos = ft_substr(k, 0, ft_strlen(k) - ft_strlen(pinpoint));
	return (eq_pos);
}

char	*replace_value(char *new)
{
	char	*new_value;
	char	*pinpoint;

	pinpoint = ft_strchr(new, '=');
	new_value = ft_strdup(pinpoint + 1);
	return (new_value);
}

char	*export_envp_value(char *k, char *v, t_shell *envp)
{
	t_envp	*ptr;
	char	*eq_pos;

	ptr = envp->head;
	eq_pos = 0;
	eq_pos = extract_key(eq_pos, k);
	while (ptr)
	{
		if (key_equals(ptr->key, eq_pos))
		{
			if (v)
			{
				free(ptr->value);
				ptr->value = replace_value(v);
			}
			free(eq_pos);
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	free(eq_pos);
	return (NULL);
}
