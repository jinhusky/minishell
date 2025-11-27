/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:34:23 by jhor              #+#    #+#             */
/*   Updated: 2025/11/27 19:52:04 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_block;
	size_t	min;

	new_block = NULL;
	min = 0;
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		ptr = malloc(sizeof(size_t) * (new_size));
		return (ptr);
	}
	new_block = malloc(new_size);
	if (old_size < new_size)
		min = old_size;
	else
		min = new_size;
	ft_memcpy(new_block, ptr, min);
	free(ptr);
	return (new_block);
}
