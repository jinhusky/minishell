/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:17 by jhor              #+#    #+#             */
/*   Updated: 2025/11/20 17:50:46 by jhor             ###   ########.fr       */
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
		// printf("*ft_expand* start:%zu\n", start);
		// printf("*ft_expand* start:%zu\n", end);
		// printf("*ft_expand* key string:%c\n", lxm[start + 1]);
		// printf("*ft_expand* key string:%c\n", lxm[start + 2]);
		// printf("*ft_expand* key string:%c\n", lxm[start + 3]);
		// printf("*ft_expand* key string:%c\n", lxm[start + 4]);
		// printf("*ft_expand* key string:%c\n", lxm[end]);
		// printf("*ft_expand* env key string:%s\n", tmp->key);
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

char	*extract_token_expand(char *lxm, size_t *i, t_parser *p)
{
	size_t	j;
	char	*value;

	j = 0;
	value = NULL;
	if (lxm[*i] == '$' && iter_dollar(lxm))
		value = ft_strdup("$");
	else if (lxm[*i] == '$' && lxm[*i + 1])
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

// char	*populate_str(char const *s, unsigned int start, size_t len)
// {
// 	unsigned int	i;
// 	char			*newstr;

// 	if (s == NULL)
// 		return (NULL);
// 	newstr = (char *)malloc(sizeof(char) * (len + 1));
// 	if (newstr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && s[start + i])
// 	{
// 		newstr[i] = s[i + start];
// 		i++;
// 	}
// 	newstr[i] = '\0';
// 	return (newstr);
// }

char	*populate_str(char *s, size_t start, size_t end)
{
	unsigned int	i;
	char			*newstr;
	unsigned int	s_len;

	if (s == NULL)
		return (NULL);
	s_len = end - start;
	newstr = (char *)malloc(sizeof(char) * (s_len + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < s_len && s[start + i])
	{
		newstr[i] = s[i + start];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*token_single_only(char *lxm, size_t *i, char *value, t_parser *p)
{
	char		quote;
	size_t		refer;
	
	quote = 0;
	refer = 0;
	if (lxm[*i] == '\'')
	{
		refer = *i;
		printf("*token_single_only* refer:%zu\n", refer);
		printf("*token_single_only* refer:%c\n", lxm[refer]);
		quote = lxm[(*i)++];
		printf("*token_single_only* quote:%c\n", quote);
	}
	while (lxm[*i] && lxm[*i] != '\'')
	{
		printf("*token_single_only* looping char:%c\n", lxm[*i]);
		(*i)++;
	}
	if (lxm[*i] == '\'')
		quote = 0;
	printf("*token_single_only* current char:%c\n", lxm[*i]);
	printf("*token_single_only* *i:%zu\n", *i);
	printf("*token_single_only* refer:%zu\n", refer);
	value = populate_str(lxm, refer, *i + 1);
	if (quote != 0)
		error_quotes(quote, p);
	printf("*token_single_only* current str:%s\n", value);
	return (value);
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
	while (i < ft_strlen(lxm))
	{
		value = NULL;
		printf("*token_expandable_check* lxm[i]:%c\n", lxm[i]);
		if (lxm[i] == '$')
		{
			value = extract_token_expand(lxm, &i, p);
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* result:%s\n", result);
			// if (iter_dollar(result) == 1) //!deals with $ sign only
			// 	break;
			printf("*token_expandable_check* iterator passed back from extract_token_expand:%zu\n", i);
			if (lxm[i] == '$' && lxm[i + 1] && lxm[i + 1] != '$')
				continue;
		}
		else if (lxm[i] != '$' && lxm[i] != '\'' && lxm[i] != '"')
		{
			ch[0] = lxm[i];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
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