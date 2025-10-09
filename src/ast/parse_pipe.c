/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/09 23:02:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//now that i have a link list of tokens, what is the next step
//i should be traversing on the link list and identify 
//what tokens it can form to be a non-terminal
//we create functions according to the grammar rules and parse  in sequences

t_ast	*init_ast(t_ast *node, t_parser *p, t_token *token)
{
	node = malloc(sizeof(t_ast));
	node->type = 0;
	node->children = NULL;
	node->childcount = 0;
	node->token_ref = NULL;
	p->cursor = token;
	return (node);
}

t_parser	*get_token(t_parser *p)
{
	if (p->cursor != NULL)
		p->cursor = p->cursor->next;
	return (p);
}

t_token	*token_peek(t_parser *p)
{
	return (p->cursor);
}

t_ast	*create_treenode(t_ast *treenode)
{
	treenode = malloc(sizeof(t_ast));
	if (!treenode)
		return (NULL);
	treenode->children = NULL;
	treenode->childcount = 0;
	treenode->token_ref = NULL;
	treenode->type = 0;
	return (treenode);
}

void	attach_treenode(t_ast *branch, t_ast *leaf) //continue here
{
	t_ast	**new_children;
	int		i;

	new_children = NULL;
	i = 0;
	if (!branch || !leaf)
		return;
	if (branch->children == NULL)
	{
		printf("*attach_node* pass here\n");
		branch->children = malloc(sizeof(t_ast *));
		if (!branch->children)
			return;
		branch->children[0] = leaf;
		branch->childcount = 1;
	}
	else //!figure out why the reallocation is not working
	{
		printf("*attach_node* entered here\n");
		printf("*attach node* parent:%p, %d\n", branch->children, branch->type);
		printf("*attach node* parent's childcout: %d\n", branch->childcount);
		new_children = realloc(branch->children, sizeof(t_ast *) * (branch->childcount + 1));
		printf("*attach node* parent:%p\n", new_children);
		if (!new_children)
			return;
		branch->children = new_children;
		printf("*attach node* new parent:%p\n", branch->children);
		printf("*attach_treenode* parent's childcount after realloc: %d\n", branch->childcount);
		printf("*attach_treenode* children's type: %d\n", leaf->type);
		branch->children[branch->childcount] = leaf;
		branch->childcount++;
		// printf("*attach_treenode* parent's children after realloc: %s\n", branch->children[0]->token_ref->lexeme);
		// printf("*attach_treenode* parent's children after realloc: %s\n", branch->children[1]->token_ref->lexeme);
		// if (branch->children != NULL)
		// 	printf("*attach_treenode* branch children: %s\n", branch->children[0]->token_ref->lexeme);
		// printf("*attach_treenode* children children: %s\n", leaf->token_ref->lexeme);
		// printf("*attach_treenode* branch childcount: %s\n", branch->children[1]->token_ref->lexeme);
	}
	return;
}

void	parse_word(t_ast *branch, t_parser *p)
{
	branch->type = AST_WORD;
	branch->token_ref = p->cursor;
	if (!branch->token_ref)
		return;
	return;
}

t_ast	*parse_argument(t_ast *chd_ptr, t_parser *p)
{
	t_ast	*word_ptr;
	
	word_ptr = NULL;
	chd_ptr = create_treenode(chd_ptr);
	chd_ptr->type = AST_ARGUMENT;
	if (!token_peek(p))
	{
		printf("*parse argument* Error: end of link-list\n");
		return (NULL);
	}
	if (token_peek(p)->token == WORD)
	{
		printf("*inside parse_arguments* cursor:%s\n", p->cursor->lexeme);
		word_ptr = create_treenode(word_ptr);
		parse_word(word_ptr, p);
		attach_treenode(chd_ptr, word_ptr);
		printf("*parse_argument* AST_ARGUMENT: %d\n", chd_ptr->type);
		for (int i = 0; i < chd_ptr->childcount; i++)
			printf("*parse_argument* AST_WORD: %d: %s\n", chd_ptr->children[i]->type, chd_ptr->children[i]->token_ref->lexeme);
	}
	return (chd_ptr);
}

bool	valid_component(t_parser *p)
{
	return (p->cursor->token == WORD
		|| p->cursor->token == REDIR_IN
		|| p->cursor->token == REDIR_OUT
		|| p->cursor->token == HEREDOC
		|| p->cursor->token == APPEND);
}

t_ast	*parse_components(t_ast *prt, t_ast *child, t_parser *p)
{
	printf("*inside parse_components* cursor:%s\n", p->cursor->lexeme);
	printf("here inside parse_component loop(0)\n");
	// if (token_peek(p))
		// return (NULL);
	printf("here inside parse_component loop(1)\n");
	while (token_peek(p) && valid_component(p))
	{
		printf("here inside parse_component loop(2)\n");
		if (token_peek(p)->token == WORD)
		{
			child = parse_argument(child, p);
			printf("*parse_components* AST_COMMAND: %d\n", prt->type);
			for (int i = 0; i < child->childcount; i++)
				printf("*parse_components(1)* AST_ARGUMENT's children: %d: %s\n", child->children[i]->type, child->children[i]->token_ref->lexeme);
			attach_treenode(prt, child);
		}
		// for (int i = 0; i < prt->childcount; i++)
		// 	printf("*parse_components(2)* parent's children %d: %s\n", prt->children[i]->type, prt->children[i]->token_ref->lexeme);
		// printf("*parse_components(3)* %d: %s\n", prt->children[1]->type, prt->children[1]->token_ref->lexeme);
		// printf("*parse_components* %d: %s\n", prt->children[1]->type, prt->children[1]->token_ref->lexeme);
		// printf("*parse_components* %d: %s\n", prt->children[2]->type, prt->children[2]->token_ref->lexeme);
		// else if (token_peek(p)->token != WORD && token_peek(p)->token != PIPE)
		// {
		// 	parse_redirection(p);
		// 	attach_treenode(prt, child);
		// }
		p = get_token(p);
	}
	return (prt);
}

void	parse_simple_command(t_ast *branch, t_parser *p)
{
	t_ast	*command;

	command = NULL;
	branch->type = AST_COMMAND;
	if (!branch->children)
	{
		command = create_treenode(command);
		parse_word(command, p); // create a fresh branch AST_COMMAND && AST_WORD following command_word -> word
		attach_treenode(branch, command);
	}
	else if (branch->children)
	{
		printf("*in here parse_simple_command*\n");
		command = parse_components(branch, command, p);
		if (command)
			printf("command ptr has content inside\n");
		attach_treenode(branch, command);
	}
	printf("*parse_sc* parent: %d\n", branch->type);
	// for (int i = 0; i < branch->childcount; i++)
	// 	printf("*parse_sc* %d: %s\n", branch->children[i]->type, branch->children[i]->token_ref->lexeme);
	return;
	// p->cursor = get_token(p);
	//else if (token_peek(p)->token == WORD) //existing AST_COMMAND branch
	//	node = parse_components(); //create AST_WORD then attach to existing AST_COMMAND
}

void	parse_pipeline(t_ast *root, t_parser *p)
{
	t_ast	*branch;

	branch = NULL;
	if (!token_peek(p))
		return;
	if (p->cur_cmd == NULL)
	{
		branch = create_treenode(branch);
		p->cur_cmd = branch;
	}
	if (token_peek(p)->token == PIPE)
	{
		p = get_token(p);
		branch = create_treenode(branch);
		p->cur_cmd = branch;
		parse_simple_command(p->cur_cmd, p);
		attach_treenode(root, p->cur_cmd);
	}
	else if (token_peek(p)->token != PIPE)
	{
		parse_simple_command(p->cur_cmd, p);
		attach_treenode(root, p->cur_cmd);
	}
	p = get_token(p);
	if (token_peek(p))
		parse_pipeline(root, p);
}





// void	parse_pipeline(t_ast *root, t_parser *p, t_ast **cur_cmd)
// {
// 	t_ast	*branch;

// 	branch = NULL; //this is causing the next recursive call to loss its reference to the previous command child
// 	if (token_peek(p) == NULL)
// 		return;
// 	if (root->childcount == 0)
// 	{
// 		branch = create_treenode(branch);
// 		*cur_cmd = branch;
// 	}
// 	if (token_peek(p)->token == PIPE)
// 	{
// 		p = get_token(p);
// 		branch = create_treenode(branch);
// 		*cur_cmd = branch;
// 		parse_simple_command(&branch, p, cur_cmd);
// 		attach_treenode(&root, branch);
// 	}
// 	else if (token_peek(p)->token != PIPE)
// 	{
// 		if (*cur_cmd)
// 			printf("malloc-ed\n");
// 		parse_simple_command(&branch, p, cur_cmd);
// 		if ((*cur_cmd)->children)
// 			printf("*inside parse_pipeline* %d\n", root->type);
// 		attach_treenode(&root, *cur_cmd);
// 		printf("*inside parse_pipeline* %d\n", root->children[0]->type);
// 	}
// 	p = get_token(p);
// 	printf("*parse_pipeline* parent type: %d\n", root->type);
// 	printf("*parse_pipeline* child of parent: %d\n", root->children[0]->type);
// 	printf("*parse_pipeline* child type: %d\n", (*cur_cmd)->type);
// 	printf("*parse_pipeline* children of child: %s\n", (*cur_cmd)->children[0]->token_ref->lexeme);
// 	// if (cur_cmd->children)
// 	// 	printf("*parse_pipeline* children of child: %s\n", cur_cmd->children[1]->token_ref->lexeme);
// 	// printf("*parse_pipeline* parent: %d\n", branch->type);
// 	// printf("*parse_pipeline* %d: %s\n", root->children[0]->type, root->children[0]->token_ref->lexeme);
// 	// for (int i = 0; i < cur_cmd->childcount; i++)
// 	// printf("*parse_pipeline* cur_cmd %d: %s\n", cur_cmd->children[0]->type, cur_cmd->children[0]->token_ref->lexeme);
// 	// printf("*parse_pipeline* cur_cmd %d: %s\n", cur_cmd->children[1]->type, cur_cmd->children[1]->token_ref->lexeme);
// 	parse_pipeline(root, p, cur_cmd);
// 	//if token_peek is WORD then call parse_simple_command;
// 	//get_token to get the next token;
// 	//if token_peek is REDIRECTION then call parse_simple_command;
// 	//if token_peek is PIPE then get_token to consume and call parse_simple_command
// 	// else if (token_peek(p)->token == REDIR_IN || 
// 	// 	token_peek(p)->token == REDIR_OUT ||
// 	// 	token_peek(p)->token == HEREDOC || token_peek(p)->token == APPEND)
// 	// 	parse_simple_command();
// 	// if (token_peek(p)->token == PIPE)
// 	// {
// 	// 	p->cursor = get_token(p);
// 	// 	parse_simple_command();
// 	// }
// 	// if (!token_peek(p))
// 		// error_handle;
// }

t_ast	*parsing(t_ast *node, t_token *token, t_parser *p)
{
	node = init_ast(node, p, token);
	if (!node)
		printf("not initialized\n");
	parse_pipeline(node, p);
	if (node)
		printf("*inside parsing* %d\n", node->type);
	// for (int i = 0; node->children[i] && i < node->childcount; i++)
	// 	printf("*parsing* %d: %s\n", node->children[i]->type, node->children[i]->token_ref->lexeme);
	return (node);
}
