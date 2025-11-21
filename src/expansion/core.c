/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:17 by jhor              #+#    #+#             */
/*   Updated: 2025/11/21 11:55:21 by jhor             ###   ########.fr       */
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
	size_t copy = start;
	printf("*ft_expand*\n");
	while (copy < end)
	{
		printf("%c", lxm[copy]);
		copy++;
	}
	printf("\n");
	printf("errflagtest: %d\n", p->err_flag);
	while (tmp)
	{
		if ((ft_strncmp(lxm + start + 1, tmp->key, key_len)) == 0
			&& ft_strlen(tmp->key) == key_len)
		{
			printf("*ft_expand* key string:%s\n", tmp->key);
			value = ft_strdup(tmp->value);
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

int	iter_dollar(char *lxm)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(lxm) && lxm[i] == '$')
		i++;
	if (i == ft_strlen(lxm))
		return (1);
	return (0);
}

int	iter_dollar_quotes(char *lxm, size_t start, t_parser *p)
{
	size_t	len;
	size_t	end;

	end = start;
	while (end < len && lxm[end] == '$')
		end++;
	len = end - (start + 1);
	if (start == len)
		return (1);
	return (0);
}

char	*extract_token_expand(char *lxm, size_t *i, t_parser *p)
{
	size_t	j;
	char	*value;

	j = 0;
	value = NULL;
	if (lxm[*i] == '$' && lxm[*i + 1])
	{
		j = *i;
		*i = *i + 1;
		while (lxm[*i] && lxm[*i] != ' ' && lxm[*i] != '"' && lxm[*i] != '\''
		&& lxm[*i] != '$')
			(*i)++;
		value = ft_expand(lxm, j, *i, p);
		printf("value[%s]\n", value);
		printf("end----------------------------------\n");
	}
	return (value);
}

char *token_single_only(char *lxm, size_t *i, t_parser *p)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*value;

	len = 0;
	value = NULL;
	start = *i;
	end = ++(*i);
	while (lxm[end] && lxm[end] != '\'')
		end++;
	if (lxm[end] != '\'')
	{
		error_quotes('\'', p);
		return (NULL);
	}
	len = end - start + 1;
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	ft_memcpy(value, lxm + start, len);
	value[len] = '\0';
	*i = end;
	return (value);
}

char	*token_double_only(char *lxm, size_t *i, t_parser *p)
{
	size_t	end;
	char	ch[2];
	char	*value;
	char	*result;
	
	// printf("*token_double_only* what is *i:%zu\n", *i);
	result = ft_strdup("");
	ch[0] = lxm[*i];
	ch[1] = 0;
	result = ft_strjoin_free(result, ft_strdup(ch));
	end = ++(*i);
	// printf("*token_double_only* what is end:%zu\n", end);
	// printf("*token_double_only* what is *i after:%zu\n", *i);
	value = NULL;
	while (lxm[end] && lxm[end] != '"')
	{
		// printf("*token_double_only* lxm[end] inside loop:%c\n", lxm[end]);
		if (lxm[end] == '$')
		{
			value = extract_token_expand(lxm, &end, p);
			// printf("*token_double_only* value from extract_token_expand:%s\n", value);
			// printf("*token_double_only* lxm[end] inside loop:%c\n", lxm[end]);
			result = ft_strjoin_free(result, value);
		}
		if (lxm[end] && lxm[end] != '$' && lxm[end] != '"')
		{
			ch[0] = lxm[end];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
		}
		// printf("*token_double_only* result inside loop:%s\n", result);
		if (lxm[end] && lxm[end] != '"')
			end++;
	}
	// printf("*token_double_only* lxm[end] after the loop:%c\n", lxm[end]);
	if (lxm[end] != '"' && lxm[end] != '$')
	{
		error_quotes('"', p);
		return (NULL);
	}
	ch[1] = 0;
	ch[0] = lxm[end];
	result = ft_strjoin_free(result, ft_strdup(ch));
	*i = end;
	return (result);
}

char	*token_expandable_check(char *lxm, t_parser *p)
{
	size_t	i;
	char	ch[2];
	char	*result;
	char	*value;
	
	i = 0;
	result = ft_strdup("");
	printf("*token_is_expandable* string passed:%s\n", lxm);
	if (iter_dollar(lxm) == 1)
	{
		result = ft_strjoin_free(result, ft_strdup("$"));
		return (result);
	}
	while (i < ft_strlen(lxm))
	{
		printf("*token_expandable_check* lxm[i]:%c\n", lxm[i]);
		printf("*token_expandable_check* i:%zu\n", i);
		if (lxm[i] == '\'')
		{
			value = token_single_only(lxm, &i, p);
			if (!value && p->err_flag == 1)
			{
				main_free(p->node, p->token, p->result, p->ptr);
				exit (2);
			}
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* single quotes result:%s\n", result);
		}
		else if (lxm[i] == '"')
		{
			value = token_double_only(lxm, &i, p);
			if (!value && p->err_flag == 1)
			{
				main_free(p->node, p->token, p->result, p->ptr);
				exit (2);
			}
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* double quotes result:%s\n", result);
		}
		else if (lxm[i] == '$')
		{
			value = extract_token_expand(lxm, &i, p);
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* result:%s\n", result);
			printf("*token_expandable_check* iterator passed back from extract_token_expand:%zu\n", i);
			continue;
		}
		else if (lxm[i] && lxm[i] != '$' && lxm[i] != '\'' && lxm[i] != '"')
		{
			ch[0] = lxm[i];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
		}
		i++;
	}
	printf("*token_expandable_check* final result:%s\n", result);
	return (result);
}

void	expand_check_quotes(t_ast *child, t_parser *p)
{
	int		i;
	char	*str;
	char	*result;
	
	result = NULL;
	printf("in here token_quotes\n");
	if (child->type == AST_WORD)
	{
		i = 0;
		str = child->token_ref->lexeme;
		result = token_expandable_check(str + i, p);
		printf("*token_single_quotes* final result:%s\n", result);
		free(result);
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
			expand_check_quotes(cmd->children[i], p);
		}
		else if (cmd->children[i]->type == AST_ARGUMENT)
		{
			expand_check_quotes(cmd->children[i]->children[0], p);
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