/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/13 18:00:38 by jhor             ###   ########.fr       */
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

	new_children = NULL;
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
	else
	{
		printf("*attach_node* entered here\n");
		if (branch->children[0]->token_ref)
			printf("*attach node* parent:%p, %s, %d\n", branch->children, branch->children[0]->token_ref->lexeme, branch->type);
		printf("*attach node* parent's childcout: %d\n", branch->childcount);
		// if (leaf->children)
			// printf("*attach_node* child's content: %s\n", leaf->children[1]->children[0]->token_ref->lexeme);
		new_children = realloc(branch->children, sizeof(t_ast *) * (branch->childcount + 1));
		printf("*attach node* parent:%p\n", new_children);
		if (!new_children)
			return;
		branch->children = new_children;
		printf("*attach node* new parent:%p\n", branch->children);
		printf("*attach_treenode* parent's childcount after realloc: %d\n", branch->childcount);
		printf("*attach_treenode* children's type: %d\n", leaf->type);
		branch->children[branch->childcount] = leaf;
		printf("*attach node* parent:%p, %d, %d\n", branch->children, branch->children[0]->type, branch->type);
		printf("*attach node* parent:%p, %d, %d\n", branch->children, branch->children[1]->type, branch->type);
		// printf("*attach node* parent:%p, %s, %d\n", branch->children, branch->children[1]->children[0]->token_ref->lexeme, branch->type);
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

bool	valid_redirection(t_parser *p)
{
	return ( p->cursor->token == REDIR_IN
		|| p->cursor->token == REDIR_OUT
		|| p->cursor->token == HEREDOC
		|| p->cursor->token == APPEND);
}

t_ast	*parse_redirection(t_ast *chd_ptr, t_parser *p, t_token *cur_redir)
{
	t_ast	*wrd_ptr;

	wrd_ptr = NULL;
	if (!token_peek(p))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(cur_redir->lexeme, 2);
		ft_putstr_fd("'\n", 2);
		exit(127);
	}
	chd_ptr = create_treenode(chd_ptr);
	wrd_ptr = create_treenode(wrd_ptr);
	if (!chd_ptr)
		ft_putstr_fd("failed to malloc in parse redirection\n", 2);
	if (token_peek(p)->token == WORD && cur_redir->token == REDIR_IN)
		chd_ptr->type = AST_REDIR_IN;
	else if (token_peek(p)->token == WORD && cur_redir->token == REDIR_OUT)
		chd_ptr->type = AST_REDIR_OUT;
	else if (token_peek(p)->token == WORD && cur_redir->token == HEREDOC)
		chd_ptr->type = AST_HEREDOC;
	else if (token_peek(p)->token == WORD && cur_redir->token == APPEND)
		chd_ptr->type = AST_APPEND;
	parse_word(wrd_ptr, p);
	attach_treenode(chd_ptr, wrd_ptr);
	return (chd_ptr);
}

void	parse_maybe_redirs(t_ast *prt, t_parser *p)
{
	t_ast	*redir_chd;
	t_token	*cur_redir;

	redir_chd = NULL;
	cur_redir = NULL;
	while (token_peek(p) && valid_redirection(p))
	{
		cur_redir = p->cursor;
		p = get_token(p);
		redir_chd = parse_redirection(redir_chd, p, cur_redir);
		printf("*inside parse_maybe_redir* child(AST_REDIR): %d, %s\n", redir_chd->type, redir_chd->children[0]->token_ref->lexeme);
		attach_treenode(prt, redir_chd);
		printf("*inside parse_maybe_redir* parent(AST_COMMAND) type: %d\n",prt->type);
		printf("*inside parse_maybe_redir* parent(AST_COMMAND)'s children: %d, %s\n", prt->children[0]->type, prt->children[0]->children[0]->token_ref->lexeme);
		p = get_token(p);
	}
	printf("*inside parse_maybe_redir* current token to return back to parse_sc is: %s\n", p->cursor->lexeme);
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
	t_token	*cur_redir;

	cur_redir = NULL;
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
		else
		{
			cur_redir = p->cursor; //!could tweak to handle the redir reference pointer inside parse_redirection
			p = get_token(p);
			child = parse_redirection(child, p, cur_redir);
			attach_treenode(prt, child);
		}
		// printf("*parse_components(2)* parent's children %d: %d\n", prt->children[0]->type, prt->children[0]->children[0]->type);
		// printf("*parse_components(2)* parent's children %d: %s\n", prt->children[1]->type, prt->children[1]->children[0]->token_ref->lexeme);
		p = get_token(p);
	}
	return (prt);
}

//TODO: When redirection functions is done, try to work out the logic of after parse_maybe_redirs, the next WORD type token should be command and just parse as AST_WORD
//TODO: handle syntax errors such as redirection without a filename etc.
//TODO: write out a program to print out your tree (with improvement from chatgpt)
//TODO: work out the code to free ast treenodes each prompt

void	parse_simple_command(t_ast *branch, t_parser *p)
{
	t_ast	*command;

	command = NULL;
	branch->type = AST_COMMAND;
	if (!branch->children && (token_peek(p)->token == REDIR_IN || 
	token_peek(p)->token == REDIR_OUT || token_peek(p)->token == APPEND || 
	token_peek(p)->token == HEREDOC))
	{
		printf("*parse_sc* inside maybe redir if statement\n");
		command = create_treenode(command);
		parse_maybe_redirs(branch, p);
		printf("*parse_sc* AST_COMMAND'S type: %d\n", branch->type);
		printf("*parse_sc* AST_REDIR's type: %d children: %d\n", branch->children[0]->type, branch->children[0]->children[0]->type);
	}
	if (!branch->children && token_peek(p)->token == WORD)
	{
		command = create_treenode(command);
		parse_word(command, p); // create a fresh branch AST_COMMAND && AST_WORD following command_word -> word
		attach_treenode(branch, command);
		p = get_token(p);
	}
	if (branch->children && token_peek(p))
	{
		printf("*in here parse_simple_command*\n");
		command = parse_components(branch, command, p);
		if (command)
			printf("command ptr has content inside\n");
		printf("*parse_sc* AST_COMMAND'S children type: %d children: %s\n", branch->children[1]->type, branch->children[1]->children[0]->token_ref->lexeme);
	}
	printf("*parse_sc* parent: %d\n", branch->type);
	for (int i = 0; i < branch->childcount; i++)
		printf("*parse_sc* %d\n", branch->children[i]->type);
	return;
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
		attach_treenode(root, p->cur_cmd);
	}
	if (token_peek(p)->token == PIPE)
	{
		p = get_token(p);
		branch = create_treenode(branch);
		p->cur_cmd = branch;
		printf("*parse_pipeline pipe statement* %d\n", p->cur_cmd->type);
		parse_simple_command(p->cur_cmd, p);
		attach_treenode(root, p->cur_cmd);
	}
	else if (token_peek(p)->token != PIPE)
		parse_simple_command(p->cur_cmd, p);
	printf("*parse_pipeline* parent: %d\n", root->type);
	printf("*parse_pipeline* parent childcount: %d\n", root->childcount);
	for (int i = 0; i < root->childcount; i++)
		printf("*parse_pipeline* %d\n", root->children[i]->type);
	if (token_peek(p) && token_peek(p)->token != PIPE)
		p = get_token(p);
	if (token_peek(p))
	{
		printf("*parse_pipeline*, %s\n", p->cursor->lexeme);
		parse_pipeline(root, p);
	}
}

t_ast	*parsing(t_ast *node, t_token *token, t_parser *p)
{
	node = init_ast(node, p, token);
	if (!node)
		printf("not initialized\n");
	parse_pipeline(node, p);
	if (node)
	{
		printf("*inside parsing* %d\n", node->type);
		printf("*parsing* %d\n", node->children[0]->type);
		// printf("*parsing* %d\n", node->children[1]->type);
		// printf("*parsing* %d\n", node->children[1]->type);

		// printf("*parsing* (1)first children of child(AST_COMMAND): %d: %s\n", node->children[0]->children[0]->type, node->children[0]->children[0]->children[0]->token_ref->lexeme);
		// printf("*parsing* (1)second children of child(AST_COMMAND): %d: %s\n", node->children[0]->children[1]->type, node->children[0]->children[1]->children[0]->token_ref->lexeme);
		// printf("*parsing* (1)third children of child(AST_COMMAND): %d\n", node->children[0]->children[2]->type);
		// printf("*parsing* (1)fourth children of child(AST_COMMAND): %d\n", node->children[0]->children[3]->type);

		// printf("*parsing* (2)first children of child(AST_COMMAND): %d: %s\n", node->children[1]->children[0]->type, node->children[1]->children[0]->children[0]->token_ref->lexeme);
		// printf("*parsing* (2)second children of child(AST_COMMAND): %d: %s\n", node->children[1]->children[1]->type, node->children[1]->children[1]->children[0]->token_ref->lexeme);
		// printf("*parsing* (1)first children of child(AST_COMMAND): %d, %d\n", node->children[0]->children[0]->type, node->children[0]->children[0]->type);
		// printf("*parsing* (1)second children of child(AST_COMMAND): %d, %d\n", node->children[0]->children[1]->type, node->children[0]->children[1]->children[0]->type);
		// printf("*parsing* (1)third children of child(AST_COMMAND): %d, %d\n", node->children[0]->children[2]->type, node->children[0]->children[2]->children[0]->type);
		// printf("*parsing* (1)fourth children of child(AST_COMMAND): %d, %d\n", node->children[0]->children[3]->type, node->children[0]->children[3]->children[0]->type);
		
		// printf("*parsing* (2)first children of child(AST_COMMAND): %d, %s\n", node->children[1]->children[0]->type, node->children[1]->children[0]->token_ref->lexeme);
		// printf("*parsing* (2)second children of child(AST_COMMAND): %d, %s\n", node->children[1]->children[1]->type, node->children[1]->children[1]->children[0]->token_ref->lexeme);
		// printf("*parsing* (2)third children of child(AST_COMMAND): %d, %s\n", node->children[1]->children[2]->type, node->children[1]->children[2]->children[0]->token_ref->lexeme);
		// printf("*parsing* (2)fourth children of child(AST_COMMAND): %d, %s\n", node->children[1]->children[3]->type, node->children[1]->children[3]->children[0]->token_ref->lexeme);

		// printf("*parsing* (3)first children of child(AST_COMMAND): %d, %s\n", node->children[2]->children[0]->type, node->children[2]->children[0]->token_ref->lexeme);
		// printf("*parsing* (3)second children of child(AST_COMMAND): %d, %s\n", node->children[2]->children[1]->type, node->children[2]->children[1]->children[0]->token_ref->lexeme);
		// printf("*parsing* (3)third children of child(AST_COMMAND): %d, %s\n", node->children[2]->children[2]->type, node->children[2]->children[2]->children[0]->token_ref->lexeme);
		// printf("*parsing* (3)fourth children of child(AST_COMMAND): %d, %s\n", node->children[2]->children[3]->type, node->children[2]->children[3]->children[0]->token_ref->lexeme);
	}
	return (node);
}
