/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:28:13 by jhor              #+#    #+#             */
/*   Updated: 2025/11/30 14:30:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**populate_argv(int *argc, char **argv, char **tokens, t_parser *p)
{
	int		i;
	int		tokens_len;

	i = -1;
	tokens_len = 0;
	if (!tokens)
		return (argv);
	if (p->malloc_flag == 1)
		return (argv);
	while (tokens[tokens_len])
		tokens_len++;
	argv = ft_realloc(argv, (*argc) * sizeof(char *),
		(*argc + tokens_len + 1) * sizeof(char *));
	if (!argv)
	{
		p->malloc_flag = 1;
		free_argv(tokens);
		return (NULL);
	}
	while (tokens[++i])
		argv[*argc + i] = ft_strdup(tokens[i]);
	*argc = (*argc + tokens_len);
	argv[*argc] = NULL;
	free_argv(tokens);
	return (argv);
}
