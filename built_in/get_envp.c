/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:37:53 by kationg           #+#    #+#             */
/*   Updated: 2025/09/20 19:08:49 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void get_envp(char **envp, t_shell *shell)
{
    int i;

    char    *delim;
    t_envp  *node;
    t_envp  *prev;

    i = 0;
    prev = NULL;
    while (envp[i])
    {
		
		node = malloc(sizeof(t_envp));
		if (i == 0)
			shell->head = node;
		if (prev)
			prev->next = node;
        delim = ft_strchr(envp[i], '=');
        node->key = ft_substr(envp[i], 0, delim - envp[i]);
        node->value = ft_substr(delim + 1,  delim - envp[i] + 1, ft_strlen(delim + 1));
		prev = node;
        i++;
    }

}

int main(int argc, char *argv[], char **envp)
{
    t_shell hey;
    get_envp(envp, &hey);
	ft_printf("%s", hey.head->key);
}
