/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:52:19 by jhor              #+#    #+#             */
/*   Updated: 2025/12/03 11:43:55 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_sc_instructor(char **result, char ***tokens, t_expand ***copies)
{
	*result = NULL;
	*tokens = NULL;
	*copies = NULL;
}

void	free_origin(t_expand *origin)
{
	if (origin->s_array)
		free(origin->s_array);
	if (origin->mark)
		free(origin->mark);
	if (origin)
		free(origin);
}

void	free_all(char *result, char **tokens, t_expand **copies, t_parser *p)
{
	free(result);
	if (tokens && p->malloc_flag == 1)
		free_argv(tokens);
	if (copies)
		free_copies(copies);
	free_origin(p->origin);
}

void	ast_word_argv_builder(t_ast *cmd, int *i, t_splt_ary *sp, t_parser *p)
{
	char		*result;
	char		**tokens;
	t_expand	**copies;

	init_sc_instructor(&result, &tokens, &copies);
	p->origin = init_origin(p->origin);
	result = stage_expand_check(cmd->children[*i], p);
	if (!result && (p->err_flag == 1 || p->malloc_flag == 1))
	{
		free_origin(p->origin);
		return ;
	}
	else 
	{
		tokens = check_expand_space(result, sp, p);
		copies = copy_array_split(p->origin->s_array, sp, copies, p);
		tokens = token_quote_removal(tokens, copies, p);
		cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
		free_all(result, tokens, copies, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return ;
	}
}

void	ast_arg_argv_builder(t_ast *cmd, int *i, t_splt_ary *sp, t_parser *p)
{
	char		*result;
	char		**tokens;
	t_expand	**copies;

	init_sc_instructor(&result, &tokens, &copies);
	p->origin = init_origin(p->origin);
	result = stage_expand_check(cmd->children[*i]->children[0], p);
	if (!result && (p->err_flag == 1 || p->malloc_flag == 1))
	{
		free_origin(p->origin);
		return ;
	}
	else
	{
		tokens = check_expand_space(result, sp, p);
		copies = copy_array_split(p->origin->s_array, sp, copies, p);
		tokens = token_quote_removal(tokens, copies, p);
		cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
		free_all(result, tokens, copies, p);
		if (p->err_flag == 1 || p->malloc_flag == 1)
			return ;
	}
}

void	simple_command_instructor(t_ast *cmd, t_splt_ary *sp, t_parser *p)
{
	int	i;

	i = 0;
	while (i < cmd->childcount)
	{
		if (cmd->children[i]->type == AST_WORD)
		{
			ast_word_argv_builder(cmd, &i, sp, p);
			if (p->err_flag == 1 || p->malloc_flag == 1)
				return ;
		}
		else if (cmd->children[i]->type == AST_ARGUMENT)
		{
			ast_arg_argv_builder(cmd, &i, sp, p);
			if (p->err_flag == 1 || p->malloc_flag == 1)
				return ;
		}
		i++;
	}
}
