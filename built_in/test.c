
/* ---------- node / operator kinds ---------- */
typedef enum e_node_type {
    ND_CMD,        // leaf: simple command (argv + redirs + assignments)
    ND_PIPE,       // left | right
    ND_AND,        // left && right
    ND_OR,         // left || right
    ND_SEQ,        // left ; right      (or newline-separated list)
    ND_SUBSHELL    // ( ... )           -- single child in 'left'
}   t_node_type;

/* ---------- redirections on a command ---------- */
typedef enum e_redir_type {
    R_IN,          // < file
    R_OUT_TRUNC,   // > file
    R_OUT_APPEND,  // >> file
    R_HEREDOC,     // << delim   (store delim, expand flag)
    R_DUP_IN,      // <&fd
    R_DUP_OUT      // >&fd
}   t_redir_type;

typedef struct s_redir {
    t_redir_type       type;
    int                fd_from;        /* e.g., 0, 1, 2 (allow 2>file etc.) */
    char              *target;         /* filename | heredoc delim | "2" (for dup) */
    int                heredoc_expand; /* 1 if unquoted (expand), 0 if quoted */
    struct s_redir    *next;
}   t_redir;

/* ---------- optional: VAR=VAL prefix assignments for a single command ---------- */
typedef struct s_assign {
    char              *key;            /* "PATH" */
    char              *value;          /* "/usr/bin" */
    struct s_assign   *next;
}   t_assign;

/* ---------- simple command payload (leaf) ---------- */
typedef struct s_cmd {
    char     **argv;       /* NULL-terminated vector: {"grep","foo",NULL} */
    t_redir  *redirs;      /* linked list of redirections (apply in order) */
    t_assign *assigns;     /* VAR=VAL prefixes that affect only this command */
}   t_cmd;

/* ---------- AST node ---------- */
typedef struct s_ast {
    t_node_type        type;
    struct s_ast      *left;           /* for ND_SUBSHELL: only 'left' is used */
    struct s_ast      *right;          /* unused for ND_CMD / ND_SUBSHELL */
    union {
        t_cmd          cmd;            /* valid iff type == ND_CMD */
        /* operators hold no extra payload */
    } as;
    /* optional: token span / debug info */
    int                tok_start;      /* index of first token in original stream */
    int                tok_end;        /* index after last token */
}   t_ast;


#include <stdio.h>
/* Set to 0 if your terminal/font hates Unicode box drawing */
#ifndef AST_PRINT_UNICODE
# define AST_PRINT_UNICODE 1
#endif

static void print_redirs(const t_redir *r, FILE *out) {
    for (; r; r = r->next) {
        const char *t = "?";
        switch (r->type) {
            case R_IN: t = "<"; break;
            case R_OUT_TRUNC: t = ">"; break;
            case R_OUT_APPEND: t = ">>"; break;
            case R_HEREDOC: t = "<<"; break;
            case R_DUP_IN: t = "<&"; break;
            case R_DUP_OUT: t = ">&"; break;
        }
        fprintf(out, " %d%s%s", r->fd_from, t, r->target ? r->target : "");
        if (r->type == R_HEREDOC) fprintf(out, "(%s)", r->heredoc_expand ? "expand" : "raw");
    }
}

static void print_cmd_inline(const t_cmd *c, FILE *out) {
    if (!c) { fputs("CMD(NULL)", out); return; }
    fputs("CMD[", out);
    if (c->argv && c->argv[0]) {
        for (int i = 0; c->argv[i]; ++i) {
            if (i) fputc(' ', out);
            fprintf(out, "%s", c->argv[i]);
        }
    } else {
        fputs("(empty)", out);
    }
    if (c->redirs) { fputs(" | redir:", out); print_redirs(c->redirs, out); }
    fputc(']', out);
}

static const char *node_name(t_node_type t) {
    switch (t) {
        case ND_CMD: return "CMD";
        case ND_PIPE: return "PIPE";
        case ND_AND: return "AND";
        case ND_OR: return "OR";
        case ND_SEQ: return "SEQ";
        case ND_SUBSHELL: return "SUBSHELL";
    }
    return "?";
}

/* Internal pretty printer */
static void print_ast_impl(const t_ast *n, const char *prefix, int is_tail, FILE *out) {
    if (!n) return;

#if AST_PRINT_UNICODE
    const char *branch = is_tail ? "└── " : "├── ";
    const char *pad    = is_tail ? "    " : "│   ";
#else
    const char *branch = is_tail ? "`-- " : "|-- ";
    const char *pad    = is_tail ? "    " : "|   ";
#endif

    fputs(prefix, out);
    fputs(branch, out);

    if (n->type == ND_CMD) {
        print_cmd_inline(&n->as.cmd, out);
    } else {
        fprintf(out, "%s", node_name(n->type));
    }
    fputc('\n', out);

    /* children: left then right */
    const t_ast *kids[2] = { n->left, n->right };
    int last_i = (kids[1] != NULL) ? 1 : 0;
    for (int i = 0; i < 2; ++i) {
        if (!kids[i]) continue;
        char next_prefix[1024];
        snprintf(next_prefix, sizeof(next_prefix), "%s%s", prefix, pad);
        print_ast_impl(kids[i], next_prefix, i == last_i, out);
    }
}

/* Public API */
static void print_ast(const t_ast *root, FILE *out) {
    if (!root) { fputs("(empty)\n", out); return; }
    print_ast_impl(root, "", 1, out);
}


/* demo.c */
#include <stdlib.h>

/* helpers (same as before) */
static t_ast *new_cmd(char **argv) { t_ast *n = calloc(1,sizeof(*n)); n->type=ND_CMD; n->as.cmd.argv=argv; return n; }
static t_ast *bin(t_node_type t, t_ast *l, t_ast *r){ t_ast *n=calloc(1,sizeof(*n)); n->type=t; n->left=l; n->right=r; return n; }

int main(void) {
    /* Example command line:
       (echo hello | tr a-z A-Z) && grep HI < in.txt >> out.txt
       Tree: AND( SUBSHELL( PIPE(echo..., tr...)), CMD(grep...) )
    */

    static char *argv_echo[] = {"echo", "hello", NULL};
    static char *argv_tr[]   = {"tr", "a-z", "A-Z", NULL};
    static char *argv_grep[] = {"grep", "HI", NULL};

    t_ast *left  = bin(ND_SUBSHELL,
                       bin(ND_PIPE,
                           new_cmd(argv_echo),
                           new_cmd(argv_tr)),
                       NULL);

    /* add a couple of redirs to grep node (optional) */
    t_redir r2 = { .type=R_OUT_APPEND, .fd_from=1, .target="out.txt", .next=NULL };
    t_redir r1 = { .type=R_IN, .fd_from=0, .target="in.txt", .next=&r2 };
    t_ast  *right = new_cmd(argv_grep);
    right->as.cmd.redirs = &r1;

    t_ast *root = bin(ND_AND, left, right);

    print_ast(root, stdout);
    return 0;
}
