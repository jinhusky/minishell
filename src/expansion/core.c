/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:09:17 by jhor              #+#    #+#             */
/*   Updated: 2025/11/27 20:41:59 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//TODO incorporate $? to get the current exit code, use t_paser struct as a global struct to store exit codes, norminette core.c

t_expand	*init_origin(t_expand *origin)
{
	origin = malloc(sizeof(t_expand));
	origin->s_array = NULL;
	origin->mark = NULL;
	origin->count = 0;
	return (origin);
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

char	*extract_token_expand(char *lxm, size_t *i, t_parser *p)
{
	size_t	start;
	char	*value;

	start = *i;
	value = NULL;
	printf("in here in extract_token_expand\n");
	if (ft_isalpha(lxm[start + 1]) || lxm[start + 1] == '_')
	{
		(*i)++;
		while (ft_isalpha(lxm[*i]) || lxm[*i] == '_')
			(*i)++;
		printf("*extract_token_expand* start:%zu\n", start);
		printf("*extract_token_expand* i:%zu\n", *i);
		value = ft_expand(lxm, start, *i, p);
			(*i)--;
		printf("*extract_token_expand* i:%zu\n", *i);
		printf("*extract_token_expand* lxm[*i]:%c\n", lxm[*i]);
		printf("value[%s]\n", value);
		printf("end----------------------------------\n");
		return (value);
	}
	printf("*extract_token_expand* i:%zu\n", *i);
	value = ft_strdup("$");
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


// int	only_dollar_quote(char *lxm, size_t start, t_parser *p)
// {
// 	size_t	i;
// 	int		dollar_sign;

// 	i = (start + 1);
// 	printf("*only_dollar_quote* i:%zu\n", i);
// 	printf("*only_dollar_quote* lxm[i]:%c\n", lxm[i]);
// 	dollar_sign = 1;
// 	while (lxm[i] && lxm[i] != '"')
// 	{
// 		if (lxm[i] != '$')
// 		{
// 			dollar_sign = 0;
// 			return (0);
// 		}
// 		i++;
// 	}
// 	p->dollar_flag = 1;
// 	return (1);
// }

char	*token_double_only(char *lxm, size_t *i, t_parser *p)
{
	printf("in here token_double_only\n");
	size_t	end;
	char	ch[2];
	char	*value;
	char	*result;
	
	result = ft_strdup("");
	value = NULL;
	printf("*token_double_only* what is *i:%zu\n", *i);
	printf("*token_double_only* what is *i after:%zu\n", *i);
	ch[0] = lxm[*i];
	ch[1] = 0;
	result = ft_strjoin_free(result, ft_strdup(ch));
	end = ++(*i);
	printf("*token_double_only* what is end:%zu\n", end);
	printf("*token_double_only* what is *i after:%zu\n", *i);
	while (lxm[end] && lxm[end] != '"')
	{
		printf("*token_double_only* lxm[end] inside loop:%c\n", lxm[end]);
		if (lxm[end] == '$')
		{
			printf("i am in here the loop\n");
			printf("*token_double_only* what is *i:%zu\n", *i);
			value = extract_token_expand(lxm, &end, p);
			if (!value && p->dollar_flag == 1)
			{
				result = ft_strjoin(result, value);
				return (result);
			}
			printf("*token_double_only* value from extract_token_expand:%s\n", value);
			printf("*token_double_only* lxm[end] inside loop:%c\n", lxm[end]);
			result = ft_strjoin_free(result, value);
		}
		else if (lxm[end] && lxm[end] != '$' && lxm[end] != '"')
		{
			ch[0] = lxm[end];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
		}
		printf("*token_double_only* result inside loop:%s\n", result);
		if (lxm[end] && lxm[end] != '"')
			end++;
	}
	printf("*token_double_only* lxm[end] after the loop:%c\n", lxm[end]);
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

//TODO test case as reference: echo "'"$SHELL $PWD $HOME $PATH"'" (TH" SKIPPED '"') FIX!! token_expandable_check 

// char	*token_expandable_check(char *lxm, t_parser *p)
// {
// 	size_t	i;
// 	char	ch[2];
// 	char	*result;
// 	char	*value;

// 	i = 0;
// 	result = ft_strdup("");
// 	if (iter_dollar(lxm) == 1)
// 	{
// 		result = ft_strjoin_free(result, ft_strdup("$"));
// 		return (result);
// 	}
	
// }

void	append_with_mark(char *value, t_expand *origin, int mark)
{
	size_t	o_len;
	size_t	len;
	size_t	new_len;
	size_t		i;

	o_len = origin->count;
	len = ft_strlen(value);
	new_len = o_len + len;
	i = 0;
	origin->s_array = ft_realloc(origin->s_array, o_len * sizeof(char *),
		(new_len  + 1) * sizeof(char *));
	ft_memcpy(origin->s_array + o_len, value, len);
	origin->s_array[new_len] = '\0';
	printf("*appen_with_mark* s_array:%s\n", origin->s_array);
	origin->mark = ft_realloc(origin->mark, o_len * sizeof(int),
		(new_len + 1) * sizeof(int));
	if (!origin->mark)
		printf("mark is empty\n");
	while (i < len)
	{
		origin->mark[o_len + i] = mark;
		i++;
	}
	origin->count = new_len;
}

void	mark_char_literal(char *value, t_parser *p)
{
	append_with_mark(value, p->origin, SRC_LITERAL);
}

void	mark_char_expand(char *value, t_parser *p)
{
	append_with_mark(value, p->origin, SRC_EXPAND);
}

char	**token_append(char **arr, char *sub, int *count)
{
	char	**new;
	int		i;

	new = NULL;
	i = 0;
	new = malloc(sizeof(char *) * (*count + 2));
	while (i < *count)
	{
		new[i] = arr[i];
		i++;
	}
	new[i++] = sub;
	new[i] = NULL;
	free(arr);
	(*count)++;
	return (new);
}

char	*substring_split(char *result, int start, int end)
{
	char	*str;
	int		i;
	
	str = NULL;
	i = 0;
	printf("*substring_split* end:%d\n", end);
	str = malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = result[start];
		start++;
		i++;
	}
	str[i] = '\0';
	printf("*substring_split* str:%s\n", str);
	return (str);
}

char	**check_expand_space(char *result, t_expand *origin)
{
	int		in_single;
	int		in_double;
	int		i;
	int		start;
	char	**tokens;
	char	*sub;
	int		tcount;

	in_single = 0;
	in_double = 0;
	i = 0;
	start = 0;
	tokens = NULL;
	sub = NULL;
	tcount = 0;
	while (result[i])
	{
		if (result[i] == '\'' && !in_double && origin->mark[i] == SRC_LITERAL)
			in_single = !in_single;
		else if (result[i] == '"' && !in_single && origin->mark[i] == SRC_LITERAL)
			in_double = !in_double;
		// printf("*check_expand_space* in_single:%d\n", in_single);
		// printf("*check_expand_space* in_double:%d\n", in_double);
		if (result[i] == ' ' && !in_single && !in_double)
		{
			printf("*check_expand_space* in_single inside the if statement:%d\n", in_single);
			printf("*check_expand_space* in_double inside the if statement:%d\n", in_double);
			if (i > start)
			{
				printf("*check_expand_space*(1) start:%d\n", start);
				printf("*check_expand_space*(1) i:%d\n", i);
				sub = substring_split(result, start, i);
				printf("*check_expand_space*(1) sub:%s\n", sub);
				tokens = token_append(tokens, sub, &tcount);
				
			}
			while (result[i] == ' ')
				i++;
			start = i;
			continue;
		}
		i++;
	}
	if (i > start)
	{
		sub = substring_split(result, start, i);
		printf("*check_expand_space* sub:%s\n", sub);
		tokens = token_append(tokens, sub, &tcount);
		printf("*check_expand_space* tcount:%d\n", tcount);
	}
	if (tokens)
	{
		tokens[tcount] = NULL;
		for (int j = 0; tokens[j]; j++)
			printf("*check_expand_space* tokens[%d]:%s\n", j, tokens[j]);
		
	}
	return (tokens);
}

char	*token_expandable_check(char *lxm, char *result, t_parser *p)
{
	size_t	i;
	char	ch[2];
	char	*lit;
	char	*value;
	
	i = 0;
	result = ft_strdup("");
	printf("*token_is_expandable* string passed:%s\n", lxm);
	// if (iter_dollar(lxm) == 1)
	// {
	// 	p->dollar_flag = 1;
	// 	result = ft_strjoin_free(result, ft_strdup("$"));
	// 	for (int i = 0; result[i]; i++)
	// 		printf("iter_dollar %c",result[i]);
	// 	return (result);
	// }
	while (i < ft_strlen(lxm))
	{
		printf("*token_expandable_check* lxm[i]:%c\n", lxm[i]);
		printf("*token_expandable_check* i:%zu\n", i);
		if (lxm[i] != '$' && lxm[i] != '\'' && lxm[i] != '"')
		{
			ch[0] = lxm[i];
			ch[1] = 0;
			result = ft_strjoin_free(result, ft_strdup(ch));
			lit = ft_strdup(ch);
			mark_char_literal(lit, p);
			free(lit);
			for (size_t o = 0; o < p->origin->count; o++)
			{
				printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
				printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			}
		}
		if (lxm[i] == '$')
		{
			value = extract_token_expand(lxm, &i, p);
			mark_char_expand(value, p);
			for (size_t o = 0; o < p->origin->count; o++)
			{
				printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
				printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			}
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* result:%s\n", result);
			printf("*token_expandable_check* iterator passed back from extract_token_expand:%zu\n", i);
		}
		else if (lxm[i] == '\'')
		{
			value = token_single_only(lxm, &i, p);
			if (!value && p->err_flag == 1)
			{
				main_free(p->node, p->token, p->result, p->ptr);
				exit (2);
			}
			mark_char_literal(value, p);
			for (size_t o = 0; o < p->origin->count; o++)
			{
				printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
				printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			}
			result = ft_strjoin_free(result, value);
			printf("*token_expandable_check* single quotes result:%s\n", result);
		}
		else if (lxm[i] == '"')
		{
			value = token_double_only(lxm, &i, p);
			if (p->err_flag == 1)
			{
				main_free(p->node, p->token, p->result, p->ptr);
				exit (2);
			}
			mark_char_literal(value, p);
			for (size_t o = 0; o < p->origin->count; o++)
			{
				printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
				printf("*token_expandable_check* current char's mark:%d\n", p->origin->mark[o]);
			}
			result = ft_strjoin_free(result, value);
			if (p->dollar_flag == 1)
			{
				p->dollar_flag = 0;
				return (result);
			}
			printf("*token_expandable_check* double quotes result:%s\n", result);
			printf("*token_expandable_check* after double quotes i:%zu\n", i);
		}
		i++;
	}
	printf("*token_expandable_check* final result:%s\n", result);
	return (result);
}

char	*stage_expand_check(t_ast *child, t_parser *p)
{
	char	*str;
	char	*result;
	
	result = NULL;
	printf("in here token_quotes\n");
	if (child->type == AST_WORD)
	{
		str = child->token_ref->lexeme;
		result = token_expandable_check(str, result, p);
		printf("*token_single_quotes* final result:%s\n", result);
		for (size_t o = 0; o < p->origin->count; o++)
		{
			printf("*token_expandable_check* current char:%c\n", p->origin->s_array[o]);
			printf("*token_expandable_check* current mark:%d\n", p->origin->mark[o]);
		}
	}
	return (result);
}

t_expand	**append_expand_token(t_expand **tkns, int *count, t_expand *orgn)
{
	tkns = ft_realloc(tkns, (*count) * sizeof(t_expand *),
		(*count + 2) * sizeof(t_expand *));
	if (!tkns)
		return NULL;
	tkns[*count] = orgn;
	(*count)++;
	tkns[*count] = NULL;
	return (tkns);
}

t_expand	*token_mark_copy(t_expand *origin, char *result, size_t start, size_t end)
{
	size_t		len;
	t_expand	*new;

	len = end - start;
	new = malloc(sizeof(t_expand));
	if (!new)
		return (NULL);
	new->s_array = NULL;
	new->s_array = malloc(sizeof(char) * (len + 1));
	if (!new->s_array)
		return (NULL);
	ft_memcpy(new->s_array, result, len);
	new->s_array[len] = '\0';
	new->mark = NULL;
	new->mark = malloc(sizeof(int) * len);
	if (!new->mark)
		return (NULL);
	ft_memcpy(new->mark, origin->mark + start, sizeof(int) * len);
	new->count = len;
	free(result);
	return (new);
}

t_expand	**copy_array_split(char *result, t_expand **cpy, t_parser *p)
{
	int			in_single;
	int			in_double;
	int			i;
	int			start;
	t_expand	**tokens;
	char		*sub;
	int			tcount;

	in_single = 0;
	in_double = 0;
	i = 0;
	start = 0;
	tokens = NULL;
	sub = NULL;
	tcount = 0;
	while (result[i])
	{
		if (result[i] == '\'' && !in_double && p->origin->mark[i] == SRC_LITERAL)
			in_single = !in_single;
		else if (result[i] == '"' && !in_single && p->origin->mark[i] == SRC_LITERAL)
			in_double = !in_double;
		// printf("*check_expand_space* in_single:%d\n", in_single);
		// printf("*check_expand_space* in_double:%d\n", in_double);
		if (result[i] == ' ' && !in_single && !in_double)
		{
			printf("*check_expand_space* in_single inside the if statement:%d\n", in_single);
			printf("*check_expand_space* in_double inside the if statement:%d\n", in_double);
			if (i > start)
			{
				printf("*check_expand_space*(1) start:%d\n", start);
				printf("*check_expand_space*(1) i:%d\n", i);
				sub = substring_split(result, start, i);
				printf("*check_expand_space*(1) sub:%s\n", sub);
				t_expand *new = token_mark_copy(p->origin, sub, start, i);
				tokens = append_expand_token(tokens, &tcount, new);
				
			}
			while (result[i] == ' ')
				i++;
			start = i;
			continue;
		}
		i++;
	}
	if (i > start)
	{
		sub = substring_split(result, start, i);
		printf("*check_expand_space* sub:%s\n", sub);
		t_expand * new = token_mark_copy(p->origin, sub, start, i);
		tokens = append_expand_token(tokens, &tcount, new);
		printf("*check_expand_space* tcount:%d\n", tcount);
	}
	if (tokens)
		tokens[tcount] = NULL;
	for (int j = 0; j < tcount; j++)
	{
		printf("*copy_array_split* tokens[%d]:%s\n", j, tokens[j]->s_array);
		printf("*copy_array_split* count[%d]:%zu\n", j, tokens[j]->count);
		for (size_t r = 0; r < tokens[j]->count; r++)
			printf("*copy_array_split* mark[%d]:%d\n", j, tokens[j]->mark[r]);
	}
	cpy = tokens;
	return (cpy);
}

void	free_copies(t_expand **copies)
{
	int	i = 0;
	while(copies[i])
	{
		free(copies[i]->s_array);
		free(copies[i]->mark);
		free(copies[i]);
		i++;
	}
	free(copies);
}

// void	expd_strp_qts(char *lxm, size_t srt, t_expd_e mk, t_parser *p)
// {
// 	char	quote;
// 	char	*src;
// 	char	*dst;

// 	init_quotes(lxm, &src, &dst);
// 	quote = 0;
// 	while (src[srt])
// 	{
// 		if ((src[srt] == '\'' || src[srt] == '"') && mk == SRC_LITERAL)
// 		{
// 			if (quote == 0)
// 				quote = src[srt];
// 			else if (quote == src[srt])
// 				quote = 0;
// 			else
// 				dst[srt++] = src[srt];
// 		}
// 		else
// 			dst[srt++] = src[srt];
// 		srt++;
// 	}
// 	dst[srt] = '\0';
// 	if (quote != 0)
// 		error_quotes(quote, p);
// 	return ;
// }

void	init_expd_quotes(size_t *si, size_t *di, char *quote)
{
	*si = 0;
	*di = 0;
	*quote = 0;
}

void	expd_strip_quotes(char *s, t_expd_e *mark, t_parser *p)
{
	size_t	si;
	size_t	di;
	char	quote;
	char	c;

	init_expd_quotes(&si, &di, &quote);
	while ((c = s[si]) != '\0')
	{
		if ((c == '\'' || c == '"') && mark[si] == SRC_LITERAL)
		{
			if (quote == 0)
				quote = c;
			else if (quote == c)
				quote = 0;
			else
				s[di++] = c;
		}
		else
			s[di++] = c;
		si++;
	}
	s[di] = '\0';
	if (quote != 0)
		error_quotes(quote, p);
}

char	**token_quote_removal(char **tkns, t_expand **cps, t_parser *p)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (tkns[i])
	{
		ptr = tkns[i];
		expd_strip_quotes(ptr, cps[i]->mark, p);
		i++;
	}
	return (tkns);
}

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
	while (tokens[tokens_len])
		tokens_len++;
	argv = ft_realloc(argv, (*argc) * sizeof(char *),
		(*argc + tokens_len + 1) * sizeof(char *));
	if (!argv)
	{
		p->malloc_flag = 1;
		return (NULL);
	}
	while (tokens[++i])
		argv[*argc + i] = ft_strdup(tokens[i]);
	*argc = (*argc + tokens_len);
	argv[*argc] = NULL;
	free_argv(tokens);
	return (argv);
}

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
			if (result)
			{
				tokens = check_expand_space(result, p->origin);
				copies = copy_array_split(p->origin->s_array, copies, p);
				tokens = token_quote_removal(tokens, copies, p);
				for (int j = 0; tokens[j]; j++)
					printf("*simple_command_instructor* tokens[%d]:%s\n", j, tokens[j]);
				for (int k = 0; tokens[k]; k++)
					printf("k:%d\n", k);
				cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
				for (int j = 0; cmd->argv[j]; j++)
					printf("*simple_command_instructor* argv[%d]:%s\n", j, cmd->argv[j]);
				for (int k = 0; cmd->argv[k]; k++)
					printf("k:%d\n", k);
				// if (p->malloc_flag == 1 && cmd->argv == NULL)
					//free everthing and exit;
				free(result);
				free_copies(copies);
				free(p->origin->s_array);
				free(p->origin->mark);
				free(p->origin);
			}
		}
		else if (cmd->children[i]->type == AST_ARGUMENT)
		{
			p->origin = init_origin(p->origin);
			result = stage_expand_check(cmd->children[i]->children[0], p);
			if (result)
			{
				tokens = check_expand_space(result, p->origin);
				copies = copy_array_split(p->origin->s_array, copies, p);
				if (!copies)
					printf("copies is empty\n");
				tokens = token_quote_removal(tokens, copies, p);
				for (int j = 0; tokens[j]; j++)
					printf("*simple_command_instructor* tokens[%d]:%s\n", j, tokens[j]);
				for (int k = 0; tokens[k]; k++)
					printf("k:%d\n", k);
				cmd->argv = populate_argv(&cmd->argc, cmd->argv, tokens, p);
				for (int j = 0; cmd->argv[j]; j++)
					printf("*simple_command_instructor* argv[%d]:%s\n", j, cmd->argv[j]);
				for (int k = 0; cmd->argv[k]; k++)
					printf("k:%d\n", k);
				free(result);
				free_copies(copies);
				free(p->origin->s_array);
				free(p->origin->mark);
				free(p->origin);
			}
		}
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
			simple_command_instructor(ptr, p);
			i++;
		}
	}
}