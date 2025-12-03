/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:56:07 by kationg           #+#    #+#             */
/*   Updated: 2025/12/03 15:47:25 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../Libft/libft.h"
# include "../minishell.h"
# include <stdbool.h>

typedef struct s_envp t_envp;
typedef struct s_shell t_shell;

int		ft_echo(char **argv);
void	ft_pwd(void);
void	get_envp(char **envp, t_shell *env);

#endif
