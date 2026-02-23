/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:22:22 by jhor              #+#    #+#             */
/*   Updated: 2026/02/24 01:22:43 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int		ft_echo(char **argv, t_globe *p);
int		ft_cd(char **argv, t_globe *p);
int		ft_pwd(char **argv, t_globe *p);
int		ft_export(char **argv, t_globe *p);
void	free_array_list(char **array, t_globe *p);
char	**bubble_sort_alpha(char **array, t_globe *p);
char	**build_array_list(t_shell *envp, t_globe *p);
int		ft_unset(char **argv, t_globe *p);
int		ft_env(char **argv, t_globe *p);
void	ft_exit(char **argv, t_globe *p);
void	invalid_numeric_msg(char *arg, t_globe *p);
char	*export_envp_value(char *k, char *v, t_shell *envp);

#endif
