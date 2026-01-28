#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"

int	ft_echo(char **argv, t_globe *p);
int	ft_cd(char **argv, t_globe *p);
int	ft_pwd(char **argv, t_globe *p);
int	ft_export(char **argv, t_globe *p);
int	ft_unset(char **argv, t_globe *p);
int	ft_env(char **argv, t_globe *p);
int	ft_exit(char **argv, t_globe *p);

#endif
