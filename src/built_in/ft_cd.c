#include "../../minishell.h"
#include <unistd.h>
#include <errno.h>

//void	print_pwd(char *str, t_shell *env)
//{
//	t_envp	*ptr;

//	ptr = env->head;
//	while (ptr)
//	{
//		if (key_equals(ptr->key, str))
//		{
//			ft_printf("PWD IN MINISHELL:%s\n", ptr->value);
//			return ;
//		}
//		ptr = ptr->next;
//	}
//}

static void	update_pwd_vars(t_globe *p, const char *oldpwd) //oldpwd is the reference to the previous pwd before cd
{
	char	*newpwd;

	if (!p || !p->envp_ls)
		return ;
	if (oldpwd)
	{
		envp_value("OLDPWD", ft_strdup((char *)oldpwd), p->envp_ls); //this is replacing the oldpwd with this new-oldpwd
	}
	newpwd = getcwd(NULL, 0); //get the new working directory as a malloc string
	if (newpwd)
		envp_value("PWD", newpwd, p->envp_ls);
}

void	cd_into_target(char **argv, char **target, t_globe *p)
{
	if (!argv || !argv[1])
		*target = envp_value("HOME", NULL, p->envp_ls);
	else
		*target = argv[1];
	if (!*target)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		p->exit_code[0] = 1;
		return ;
	}
}

int	cd_argv_count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_cd(char **argv, t_globe *p)
{
	char	*target;
	char	*oldpwd;

	if (cd_argv_count(argv) <= 2)
	{
		oldpwd = envp_value("PWD", NULL, p->envp_ls);
		cd_into_target(argv, &target, p);
		if (chdir(target) != 0)
		{
			perror("cd");
			p->exit_code[0] = 1;
			return (p->exit_code[0]);
		}
		update_pwd_vars(p, oldpwd);
		p->exit_code[0] = 0;
	}
	else
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		p->exit_code[0] = 1;
	}
	return (p->exit_code[0]);
}
