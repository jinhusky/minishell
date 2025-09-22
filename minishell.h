/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:03 by jhor              #+#    #+#             */
/*   Updated: 2025/09/22 18:09:32 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef enum	e_token //!lexical grouping
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}t_token_type;

typedef struct s_token //tokenization nodes
{
	t_token_type	token;
	char			*lexeme;
	struct s_token	*next;
}t_token;


// typedef struct s_ast {
// 	t_token *token;
// 	t_ast *right;
// 	t_ast *left;
// } t_ast;

// typedef struct	s_token
// {
// 	int index;
// 	t_token_type token;
// 	char **basinbuff;
// 	struct s_token *next;
// } t_token;

// typedef struct s_pipe
// {
	
	
	
// };

t_token	*create_node(t_token *head, char *start, size_t end);
t_token	*append_node(t_token *head, char *start, size_t end);
t_token	*append_word_node(t_token *head, char *start, size_t n_start, size_t end);
int		error_syntax(t_token *token);

#endif