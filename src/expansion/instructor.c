/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:52:19 by jhor              #+#    #+#             */
/*   Updated: 2025/11/28 17:29:31 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	simple_command_instructor(t_ast *cmd, t_parser *p)
{
	int			i;
	char		*result;
	char		**tokens;
	t_expand	**copies;

	i = 0;
	result = NULL;
	tokens = NULL;
	while (i < cmd->childcount)
	{
		copies = NULL;
		if (cmd->children[i]->type == AST_WORD)
		{
			p->origin = init_origin(p->origin);
			result = stage_expand_check(cmd->children[i], p);
			if (!result && (p->err_flag == 1 || p->malloc_flag == 1))
			{
				free(p->origin->s_array);
				free(p->origin->mark);
				free(p->origin);
				return ;
			}
			else 
			{
				tokens = check_expand_space(result, p->origin, p);
				copies = copy_array_split(p->origin->s_array, copies, p);
				tokens = token_quote_removal(tokens, copies, p);
				if (tokens)
				{
					for (int j = 0; tokens[j]; j++)
						printf("*simple_command_instructor* tokens[%d]:%s\n", j, tokens[j]);
					for (int k = 0; tokens[k]; k++)
						printf("k:%d\n", k);
				}
				cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
				if (cmd->argv)
				{
					for (int j = 0; cmd->argv[j]; j++)
						printf("*simple_command_instructor* argv[%d]:%s\n", j, cmd->argv[j]);
					for (int k = 0; cmd->argv[k]; k++)
						printf("k:%d\n", k);
				}
				free(result);
				if (tokens && p->malloc_flag == 1)
					free_argv(tokens);
				if (copies)
					free_copies(copies);
				if (p->origin->s_array)
					free(p->origin->s_array);
				if (p->origin->mark)
					free(p->origin->mark);
				if (p->origin)
					free(p->origin);
				if (p->err_flag == 1 || p->malloc_flag == 1)
					return ;
			}
		}
		else if (cmd->children[i]->type == AST_ARGUMENT)
		{
			p->origin = init_origin(p->origin);
			result = stage_expand_check(cmd->children[i]->children[0], p);
			if (!result && (p->err_flag == 1 || p->malloc_flag == 1))
			{
				free(p->origin->s_array);
				free(p->origin->mark);
				free(p->origin);
				return ;
			}
			else
			{
				tokens = check_expand_space(result, p->origin, p);
				copies = copy_array_split(p->origin->s_array, copies, p);
				tokens = token_quote_removal(tokens, copies, p);
				if (tokens)
				{
					for (int j = 0; tokens[j]; j++)
						printf("*simple_command_instructor* tokens[%d]:%s\n", j, tokens[j]);
					for (int k = 0; tokens[k]; k++)
						printf("k:%d\n", k);
				}
				cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
				if (cmd->argv)
				{
					for (int j = 0; cmd->argv[j]; j++)
						printf("*simple_command_instructor* argv[%d]:%s\n", j, cmd->argv[j]);
					for (int k = 0; cmd->argv[k]; k++)
						printf("k:%d\n", k);
				}
				free(result);
				if (tokens && p->malloc_flag == 1)
					free_argv(tokens);
				if (copies)
					free_copies(copies);
				if (p->origin->s_array)
					free(p->origin->s_array);
				if (p->origin->mark)
					free(p->origin->mark);
				if (p->origin)
					free(p->origin);
				if (p->err_flag == 1 || p->malloc_flag == 1)
				{
					printf("err_flag:%d\n", p->err_flag);
					printf("malloc_flag:%d\n", p->malloc_flag);
					printf("here\n");
					return ;
				}
			}
		}
		i++;
	}
}
