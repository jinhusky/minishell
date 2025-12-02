/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:52:19 by jhor              #+#    #+#             */
/*   Updated: 2025/12/02 15:16:08 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	simple_command_instructor(t_ast *cmd, t_splt_ary *sp, t_parser *p)
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
				tokens = check_expand_space(result, sp, p);
				copies = copy_array_split(p->origin->s_array, sp, copies, p);
				tokens = token_quote_removal(tokens, copies, p);
				cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
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
				tokens = check_expand_space(result, sp, p);
				copies = copy_array_split(p->origin->s_array, sp, copies, p);
				tokens = token_quote_removal(tokens, copies, p);
				cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
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
		i++;
	}
}
