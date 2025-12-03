/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:19:04 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 10:55:15 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_expand(char *lxm, size_t start, size_t end, t_parser *p)
{
	char	*value;
	t_envp	*tmp;
	size_t	key_len;

	value = NULL;
	tmp = p->ptr;
	key_len = end - (start + 1);
	while (tmp)
	{
		if ((ft_strncmp(lxm + start + 1, tmp->key, key_len)) == 0
			&& ft_strlen(tmp->key) == key_len)
		{
			value = ft_strdup(tmp->value);
			if (!value)
				p->malloc_flag = 1;
		}
		tmp = tmp->next;
	}
	if (value == NULL)
	{
		value = ft_strdup("");
		return (value);
	}
	else
		return (value);
}

char	*extract_token_expand(char *lxm, size_t *i, t_parser *p)
{
	size_t	start;
	char	*value;

	start = *i;
	value = NULL;
	if (ft_isalpha(lxm[start + 1]) || lxm[start + 1] == '_')
	{
		(*i)++;
		while (ft_isalpha(lxm[*i]) || lxm[*i] == '_')
			(*i)++;
		value = ft_expand(lxm, start, *i, p);
			(*i)--;
		return (value);
	}
	else if (lxm[start + 1] == '?')
	{
		value = ft_itoa(p->exit_code[0]);
		if (!value)
			p->malloc_flag = 1;
		(*i)++;
		return (value);
	}
	value = ft_strdup("$");
	return (value);
}
