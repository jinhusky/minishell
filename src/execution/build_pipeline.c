/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 23:09:42 by kationg           #+#    #+#             */
/*   Updated: 2025/12/06 23:27:43 by kationg          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    walk_ast(t_node *node, )
{
    int i;
    t_node  *ptr;

    i = 0;
    while (i < node->childcount)
    {
        ptr = node->children[i];
        walk_ast(ptr);
        i++;
    }
}
void    build_pipeline(t_node *root, t_globe *p)
{
    int argc;

    argc = count_argc(root);

}
