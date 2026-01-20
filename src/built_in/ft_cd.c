#include "../../minishell.h"
#include <unistd.h>
#include <errno.h>

static void	update_pwd_vars(t_globe *p, const char *oldpwd)
{
	char	*newpwd;

	if (!p || !p->envp_ls)
		return ;
	if (oldpwd)
		envp_value("OLDPWD", (char *)oldpwd, p->envp_ls);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		envp_value("PWD", newpwd, p->envp_ls);
		free(newpwd);
	}
}

int	ft_cd(char **argv, t_globe *p)
{
	char	*target;
	char	*oldpwd;

	oldpwd = envp_value("PWD", NULL, p->envp_ls);
	if (!argv || !argv[1])
		target = envp_value("HOME", NULL, p->envp_ls);
	else
		target = argv[1];
	if (!target)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		p->exit_code[0] = 1;
		return (p->exit_code[0]);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		p->exit_code[0] = 1;
		return (p->exit_code[0]);
	}
	update_pwd_vars(p, oldpwd);
	p->exit_code[0] = 0;
	return (p->exit_code[0]);
}
