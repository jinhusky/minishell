/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:13:33 by jhor              #+#    #+#             */
/*   Updated: 2025/10/17 19:24:21 by jhor             ###   ########.fr       */
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
	p->err_flag = 0;
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
		// printf("*attach_node* pass here\n");
		branch->children = malloc(sizeof(t_ast *));
		if (!branch->children)
			return;
		branch->children[0] = leaf;
		branch->childcount = 1;
	}
	else
	{
		// printf("*attach_node* entered here\n");
		// if (branch->children[0]->token_ref)
		// 	printf("*attach node* parent:%p, %s, %d\n", branch->children, branch->children[0]->token_ref->lexeme, branch->type);
		// printf("*attach node* parent's childcout: %d\n", branch->childcount);
		// if (leaf->children)
			// printf("*attach_node* child's content: %s\n", leaf->children[1]->children[0]->token_ref->lexeme);
		new_children = realloc(branch->children, sizeof(t_ast *) * (branch->childcount + 1));
		// printf("*attach node* parent:%p\n", new_children);
		if (!new_children)
			return;
		branch->children = new_children;
		// printf("*attach node* new parent:%p\n", branch->children);
		// printf("*attach_treenode* parent's childcount after realloc: %d\n", branch->childcount);
		// printf("*attach_treenode* children's type: %d\n", leaf->type);
		branch->children[branch->childcount] = leaf;
		// printf("*attach node* parent:%p, %d, %d\n", branch->children, branch->children[0]->type, branch->type);
		// printf("*attach node* parent:%p, %d, %d\n", branch->children, branch->children[1]->type, branch->type);
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

void strip_quotes(char *lexeme, t_parser *p) //!handle incomplete quotes
{
	char *src = lexeme;
	char *dst = lexeme;
	char quote = 0;

	while (*src)
	{
		if (*src == '\'' || *src == '"')
		{
			if (quote == 0)
				quote = *src;
			else if (quote == *src)
				quote = 0;
			else
				*dst++ = *src;
		}
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	if (quote != 0)
	{
		p->err_flag = 1;
		return;
	}
	return;
}

void	parse_word(t_ast *branch, t_parser *p)
{
	branch->type = AST_WORD;
	if (p->cursor)
	{
		//TODOD: if (inside the string has open and close double quotes as well as a '$' then call function to expand)
		strip_quotes(p->cursor->lexeme, p);
		if (p->err_flag == 1)
		{
			ft_putstr_fd("bash: unexpected EOF while ", 2);
			ft_putstr_fd("looking for matching `\"'\n", 2);
			ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
			return;
		}
		branch->token_ref = p->cursor;
	}
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
	if (!token_peek(p) || token_peek(p)->token != WORD)
	{
		error_redir(p->cursor);
		p->err_flag = 1;
		return (chd_ptr);
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
		if (p->err_flag == 1)
			return;
		// printf("*inside parse_maybe_redir* child(AST_REDIR): %d, %s\n", redir_chd->type, redir_chd->children[0]->token_ref->lexeme);
		attach_treenode(prt, redir_chd);
		// printf("*inside parse_maybe_redir* parent(AST_COMMAND) type: %d\n",prt->type);
		// printf("*inside parse_maybe_redir* parent(AST_COMMAND)'s children: %d, %s\n", prt->children[0]->type, prt->children[0]->children[0]->token_ref->lexeme);
		p = get_token(p);
	}
	// printf("*inside parse_maybe_redir* current token to return back to parse_sc is: %s\n", p->cursor->lexeme);
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
		// printf("inside parse_argument\n");
		// printf("*inside parse_arguments* cursor:%s\n", p->cursor->lexeme);
		word_ptr = create_treenode(word_ptr);
		parse_word(word_ptr, p);
		attach_treenode(chd_ptr, word_ptr);
		// printf("*parse_argument* AST_ARGUMENT: %d\n", chd_ptr->type);
		// for (int i = 0; i < chd_ptr->childcount; i++)
		// 	printf("*parse_argument* AST_WORD: %d: %s\n", chd_ptr->children[i]->type, chd_ptr->children[i]->token_ref->lexeme);
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
	// printf("*inside parse_components* cursor:%s\n", p->cursor->lexeme);
	// printf("here inside parse_component loop(0)\n");
	if (!token_peek(p))
		return (NULL);
	// printf("here inside parse_component loop(1)\n");
	while (token_peek(p) && valid_component(p))
	{
		// printf("here inside parse_component loop(2)\n");
		if (token_peek(p)->token == WORD)
		{
			// printf("here inside parse_component loop(3)\n");
			child = parse_argument(child, p);
			// printf("*parse_components* AST_COMMAND: %d\n", prt->type);
			// for (int i = 0; i < child->childcount; i++)
			// 	printf("*parse_components(1)* AST_ARGUMENT's children: %d: %s\n", child->children[i]->type, child->children[i]->token_ref->lexeme);
			attach_treenode(prt, child);
		}
		else
		{
			cur_redir = p->cursor;
			p = get_token(p);
			child = parse_redirection(child, p, cur_redir);
			if (p->err_flag == 1)
				return (prt);
			attach_treenode(prt, child);
		}
		// printf("*parse_components(2)* parent's children %d: %d\n", prt->children[0]->type, prt->children[0]->children[0]->type);
		// printf("*parse_components(2)* parent's children %d: %s\n", prt->children[1]->type, prt->children[1]->children[0]->token_ref->lexeme);
		p = get_token(p);
	}
	// printf("*parse_components* token sending back %s\n", p->cursor->lexeme);
	return (prt);
}

//TODO: (*)When redirection functions is done, try to work out the logic of after parse_maybe_redirs, the next WORD type token should be command and just parse as AST_WORD
//TODO: (*)handle syntax errors such as redirection without a filename etc, base it on the bash behaviour.
//TODO: (*)strips the quotes when parsing into AST_WORD
//TODO: (*)write out a program to print out your tree (with improvement from chatgpt)
//TODO: (*)work out the code to free ast treenodes each prompt
//TODO: (*)handle "", spaces without argument, reprompt

bool	all_redirs(t_ast *branch)
{
	int	i;

	i = 0;
	// printf("*all_redir* in here\n");
	if (!branch || branch->childcount == 0)
		return (false);
	while (i < branch->childcount)
	{
		// printf("*all_redir* in the loop\n");
		// printf("*all_redir* children's type: %d\n", branch->children[i]->type);
		// printf("*all_redir* children's children: %s\n", branch->children[i]->children[0]->token_ref->lexeme);
		if (branch->children[i]->type != AST_REDIR_IN
		&& branch->children[i]->type != AST_REDIR_OUT
		&& branch->children[i]->type != AST_APPEND
		&& branch->children[i]->type != AST_HEREDOC)
			return (false);
		i++;
	}
	// printf("*all_redir* end of function\n");
	return (true);
}

void	parse_simple_command(t_ast *branch, t_parser *p)
{
	t_ast	*command;

	command = NULL;
	branch->type = AST_COMMAND;
	if (!branch->children && (token_peek(p)->token == REDIR_IN || 
	token_peek(p)->token == REDIR_OUT || token_peek(p)->token == APPEND || 
	token_peek(p)->token == HEREDOC))
	{
		// printf("*parse_sc* inside maybe redir if statement\n");
		// command = create_treenode(command);
		parse_maybe_redirs(branch, p);
		if (p->err_flag == 1)
			return;
		// printf("*parse_sc* AST_COMMAND'S type: %d\n", branch->type);
		// printf("*parse_sc* AST_REDIR's type: %d children: %d\n", branch->children[0]->type, branch->children[0]->children[0]->type);
	}
	// printf("*parse_sc* token: %s\n", p->cursor->lexeme);
	if ((all_redirs(branch) == true || !branch->children) &&
		token_peek(p) && token_peek(p)->token == WORD)
	{
		command = create_treenode(command);
		parse_word(command, p); // create a fresh branch AST_COMMAND && AST_WORD following command_word -> word
		attach_treenode(branch, command);
		if (p->err_flag == 1)
			return;
		p = get_token(p);
	}
	// printf("*parse_sc* token reference: %s\n", p->cursor->lexeme);
	if (branch->children && token_peek(p))
	{
		// printf("*in here parse_simple_command*\n");
		command = parse_components(branch, command, p);
		if (p->err_flag == 1)
			return;
		// if (command)
		// 	printf("command ptr has content inside\n");
		// printf("*parse_sc* AST_COMMAND'S children type: %d children: %s\n", branch->children[1]->type, branch->children[1]->children[0]->token_ref->lexeme);
	}
	// printf("*parse_sc* parent: %d\n", branch->type);
	// for (int i = 0; i < branch->childcount; i++)
	// 	printf("*parse_sc* %d\n", branch->children[i]->type);
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
	// printf("what is p: %s\n", p->cursor->lexeme);
	if (token_peek(p)->token == PIPE)
	{
		if (!root->children[0]->children)
		{
			error_pipe(p->cursor);
			free_treenode(root);
			p->err_flag = 1;
			return;
		}
		p = get_token(p);
		// printf("what is p: %s\n", p->cursor->lexeme);
		if (!p->cursor || token_peek(p)->token == PIPE)
		{
			// printf("here\n");
			error_pipe(p->cursor);
			free_treenode(root);
			p->err_flag = 1;
			return;
		}
		branch = create_treenode(branch);
		p->cur_cmd = branch;
		// printf("*parse_pipeline pipe statement* %d\n", p->cur_cmd->type);
		parse_simple_command(p->cur_cmd, p);
		attach_treenode(root, p->cur_cmd);
		if (p->err_flag == 1)
		{
			free_treenode(root);
			return;
		}
	}
	else if (token_peek(p)->token != PIPE)
	{
		parse_simple_command(p->cur_cmd, p);
		if (p->err_flag == 1)
		{
			free_treenode(root);
			return;
		}
	}
	// printf("*parse_pipeline* parent: %d\n", root->type);
	// printf("*parse_pipeline* parent childcount: %d\n", root->childcount); //!uncomment if needed for debug (311 - 314)
	// for (int i = 0; i < root->childcount; i++)
		// printf("*parse_pipeline* %d\n", root->children[i]->type);
	if (token_peek(p) && token_peek(p)->token != PIPE)
		p = get_token(p);
	if (token_peek(p))
	{
		// printf("*parse_pipeline*, %s\n", p->cursor->lexeme);
		parse_pipeline(root, p);
	}
}

t_ast	*parsing(t_ast *node, t_token *token, t_parser *p)
{
	node = init_ast(node, p, token);
	parse_pipeline(node, p);
	if (p->err_flag == 1)
		return (NULL);
	return (node);
}
