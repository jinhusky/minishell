
#ifndef AST_H
#define AST_H

#include <stdlib.h>

/* ========= Node & Redirection Kinds (mandatory only) ========= */

typedef enum e_node_kind {
    NODE_CMD = 0,   /* leaf: a simple command with argv + redirs */
    NODE_PIPE       /* internal: left | right */
}   t_node_kind;

typedef enum e_redir_kind {
    R_IN = 0,       /* < file            (read)          -> fd usually 0 */
    R_OUT_TRUNC,    /* > file            (write, trunc)  -> fd usually 1 */
    R_OUT_APPEND,   /* >> file           (write, append) -> fd usually 1 */
    R_HEREDOC       /* << DELIM          (heredoc)       -> fd usually 0 */
}   t_redir_kind;

/* ========= Redirection List ========= */

typedef struct s_redir {
    t_redir_kind        kind;
    int                 fd;     /* target fd inside the command (0/1/2). for mandatory you’ll mostly use 0 or 1 */
    char               *arg;    /* filename for <,>,>> or delimiter for << (dup'ed) */
    struct s_redir     *next;
}   t_redir;

/* ========= Command Payload ========= */

typedef struct s_cmd {
    char    **argv;     /* NULL-terminated, argv[0] is the program/builtin name (dup'ed) */
    t_redir *redirs;    /* singly-linked list of redirections */
}   t_cmd;

/* ========= AST Node ========= */

typedef struct s_ast {
    t_node_kind kind;
    union {
        t_cmd cmd;          /* when kind == NODE_CMD */
        struct {            /* when kind == NODE_PIPE */
            struct s_ast *left;   /* left side of the pipe */
            struct s_ast *right;  /* right side of the pipe */
        } pipe;
    } as;
}   t_ast;

/* ========= Public API =========
   All functions return NULL/-1 on allocation errors. Ownership rules:
   - Builder functions DUP everything they need, so you can free your inputs.
   - Free with ast_free().
*/

/* Build a command node from a NULL-terminated array of strings (argv). */
t_ast   *ast_cmd_new(char *const argv[]);

/* Append a redirection to a command node.
   - kind: one of R_IN/R_OUT_TRUNC/R_OUT_APPEND/R_HEREDOC
   - fd:   which fd to redirect (0 for stdin, 1 for stdout, 2 for stderr).
           For mandatory use-cases, you’ll typically pass 0 for R_IN/R_HEREDOC,
           1 for R_OUT_*.
   - arg:  filename (for <, >, >>) or delimiter (for <<). Will be dup'ed.
*/
int      ast_cmd_add_redir(t_ast *cmd_node, t_redir_kind kind, int fd, const char *arg);

/* Build a pipe node: left | right. Takes ownership of left/right pointers. */
t_ast   *ast_pipe_new(t_ast *left, t_ast *right);

/* Free the entire tree (recursively). */
void     ast_free(t_ast *node);

/* Debug pretty-printer to visualize the tree. */
void     ast_debug_print(const t_ast *node);

#endif /* AST_H */
