/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:04:26 by kationg           #+#    #+#             */
/*   Updated: 2025/09/29 12:49:49 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

void	simple_handler(int signum)
{
	{
        write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*

int main(int argc, char *argv[], char **envp)
{
    char    *line;
	struct sigaction act;

	int fd = fork();
	if (fd == -1)
	{
		perror("Failed to fork shell");
		return (1);
	}
	if (fd != 0)
	{
		signal(SIGINT, SIG_IGN);
		wait(NULL);
	}
	else if (fd == 0)
	{
		signal(SIGINT, simple_handler);
		while (1)
		{
			char **args;
			line = readline("minishell: ");
			if (!line)
				break;
			else 
				add_history(line);    
		}
		rl_clear_history();
		
	}
}
*/
