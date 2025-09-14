/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:03 by jhor              #+#    #+#             */
/*   Updated: 2025/09/14 18:50:26 by jhor             ###   ########.fr       */
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

typedef struct s_token
{
	t_token_type	token;
	char			*lexeme;
	struct s_token	*next;
}t_token;

// typedef struct s_union
// {
// 	t_word	*word;
// }t_union;

// typedef struct s_pipe
// {
// 	t_union	*linker;
// }t_pipe;

// typedef struct s_operator
// {
	
// }t_operator;

t_token	*create_node(t_token *head, char *start, size_t end);
t_token	*append_node(t_token *head, char *start, size_t end);

#endif