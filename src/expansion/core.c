/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:17 by jhor              #+#    #+#             */
/*   Updated: 2025/11/19 18:41:33 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_expand(char *lxm, int end, t_parser *p)
{
	int i = 0;
	while (i < end)
	{
		printf("char: %c\n", lxm[i]);
		i++;
	}
	printf("errflagtest: %d\n", p->err_flag);
	// if (ft_strncmp())
}

void	extract_token_expand(char *lxm, int *i, t_parser *p)
{
	printf("iterator:%d\n", *i);
	if (lxm[*i] == '$')
	{
		*i = *i + 1;
		while (lxm[*i] && lxm[*i] != ' ' && lxm[*i] != '"' && lxm[*i] != '\''
		&& lxm[*i] != '$')
			(*i)++;
		ft_expand(lxm, *i, p);
		printf("end----------------------------------\n");
	}
	else
		return ;
}

int	token_has_single(char *lxm)
{
	int		i;

	i = 0;
	while (lxm[i])
	{
		if (lxm[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

void	token_expandable_check(char *lxm, t_parser *p)
{
	int		i;
	char	*quote;
	int		j;
	int		len;

	i = 0;
	quote = NULL;
	len = ft_strlen(lxm);
	printf("*token_is_expandable* string passed:%s\n", lxm);
	while (i < len)
	{
		printf("*token_expandable_check* lxm[i]:%c\n", lxm[i]);
		j = 0;
		if (lxm[i] == '$')
		{
			extract_token_expand(lxm, &i, p);
			printf("*token_expandable_check* iterator passed back from extract_token_expand:%d\n", i);
			if (lxm[i] == '$')
				i--;
		}
		// if (lxm[i] == '"' && !quote)
		// {
		// 	j = i;
		// 	quote = lxm[j++];
		// 	while (lxm[j] && lxm[j] != *quote)
		// 		j++;
		// 	if (lxm[j] == *quote)
		// 		quote = NULL;
		// 	if (lxm[j] == '$')
		// 		extract_token_string(lxm + i, quote, p);
		// }
		i++;
	}
}

void	token_single_quotes(t_ast *child, t_parser *p)
{
	int		i;
	char	*str;

	printf("in here token_quotes\n");
	if (child->type == AST_WORD)
	{
		i = 0;
		str = child->token_ref->lexeme;
		if ((token_has_single(str)) == 0)
		{
			strip_quotes(str, p);
			if (p->err_flag == 1)
			{
				main_free(p->node, p->token, p->result, p->ptr);
				exit(2);
			}
			return ;
		}
		token_expandable_check(str, p);
	}
}

void	command_instructor(t_ast *cmd, t_parser *p)
{
	int	i;

	i = 0;
	while (i < cmd->childcount)
	{
		if (cmd->children[i]->type == AST_WORD)
		{
			token_single_quotes(cmd->children[i], p);
		}
		else if (cmd->children[i]->type == AST_ARGUMENT)
		{
			token_single_quotes(cmd->children[i]->children[0], p);
		}
		// else if(cmd->children[i]->type == AST_REDIR_IN
		// 	|| cmd->children[i]->type == AST_REDIR_OUT
		// 	|| cmd->children[i]->type == AST_HEREDOC
		// 	|| cmd->children[i]->type == AST_APPEND)
		// {
		// 	redir_token_single_quotes(cmd->children[i]->children[0],
		// 		cmd->children[i]->type);
		// }
		i++;
	}
}

void	expansion_engine(t_ast *root, t_parser *p)
{
	int		i;
	t_ast	*ptr;

	i = 0;
	if (root)
	while (i < root->childcount)
	{
		{
			ptr = root->children[i];
			command_instructor(ptr, p);
			i++;
		}
	}
}