/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:00:15 by jhor              #+#    #+#             */
/*   Updated: 2025/09/08 20:57:27 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int main(int argc, char **argv)
{
	// if (argc < 2)
	// 	return (1);
	(void)argv;
	(void)argc;
	char *result = NULL;
	
	while (1)
	{
		result = readline("minishell$ ");
		if (!result)
			break;
		add_history(result);
		free(result);
	}
	return (0);
}
