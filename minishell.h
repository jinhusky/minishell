/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:01:03 by jhor              #+#    #+#             */
/*   Updated: 2025/09/09 15:43:06 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

enum	e_token //!lexical grouping
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC	
};

typedef struct s_word
{
	void	*cmd;
	void	*args;
	void	*filename;
}t_word;

typedef struct s_union
{
	t_word	*word;
}t_union;

typedef struct s_pipe
{
	t_union	*linker;
}t_pipe;

// typedef struct s_operator
// {
	
// }t_operator;

#endif