
#include "includes/ast.h"
#include <string.h>
#include <stdio.h>

/* ========= small utils ========= */

static void *xmalloc(size_t n) {
    void *p = malloc(n);
    return p;
}

static char *xstrdup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *p = xmalloc(n);
    if (!p) return NULL;
    memcpy(p, s, n);
    return p;
}

static char **dup_argv(char *const av[]) {
    size_t n = 0;
    while (av && av[n]) n++;
    char **copy = (char **)xmalloc(sizeof(char *) * (n + 1));
    if (!copy) return NULL;
    for (size_t i = 0; i < n; i++) {
        copy[i] = xstrdup(av[i]);
        if (!copy[i]) {
            for (size_t k = 0; k < i; k++) free(copy[k]);
            free(copy);
            return NULL;
        }
    }
    copy[n] = NULL;
    return copy;
}

/* ========= constructors ========= */

t_ast *ast_cmd_new(char *const argv[]) {
    if (!argv || !argv[0]) return NULL;
    t_ast *node = (t_ast *)xmalloc(sizeof(*node));
    if (!node) return NULL;
    node->kind = NODE_CMD;
    node->as.cmd.redirs = NULL;
    node->as.cmd.argv = dup_argv(argv);
    if (!node->as.cmd.argv) {
        free(node);
        return NULL;
    }
    return node;
}

int ast_cmd_add_redir(t_ast *cmd_node, t_redir_kind kind, int fd, const char *arg) {
    if (!cmd_node || cmd_node->kind != NODE_CMD) return -1;
    t_redir *r = (t_redir *)xmalloc(sizeof(*r));
    if (!r) return -1;
    r->kind = kind;
    r->fd = fd;
    r->arg = xstrdup(arg ? arg : "");
    if (!r->arg) { free(r); return -1; }
    r->next = NULL;

    /* append to tail (preserves order) */
    if (!cmd_node->as.cmd.redirs) {
        cmd_node->as.cmd.redirs = r;
    } else {
        t_redir *it = cmd_node->as.cmd.redirs;
        while (it->next) it = it->next;
        it->next = r;
    }
    return 0;
}

t_ast *ast_pipe_new(t_ast *left, t_ast *right) {
    if (!left || !right) return NULL;
    t_ast *node = (t_ast *)xmalloc(sizeof(*node));
    if (!node) return NULL;
    node->kind = NODE_PIPE;
    node->as.pipe.left = left;
    node->as.pipe.right = right;
    return node;
}

/* ========= destructors ========= */

static void free_redirs(t_redir *r) {
    while (r) {
        t_redir *n = r->next;
        free(r->arg);
        free(r);
        r = n;
    }
}

static void free_cmd(t_cmd *c) {
    if (!c) return;
    if (c->argv) {
        for (size_t i = 0; c->argv[i]; i++) free(c->argv[i]);
        free(c->argv);
    }
    free_redirs(c->redirs);
}

void ast_free(t_ast *node) {
    if (!node) return;
    if (node->kind == NODE_CMD) {
        free_cmd(&node->as.cmd);
    } else if (node->kind == NODE_PIPE) {
        ast_free(node->as.pipe.left);
        ast_free(node->as.pipe.right);
    }
    free(node);
}

/* ========= debug printer ========= */

static const char *redir_kind_str(t_redir_kind k) {
    switch (k) {
        case R_IN:         return "<";
        case R_OUT_TRUNC:  return ">";
        case R_OUT_APPEND: return ">>";
        case R_HEREDOC:    return "<<";
        default:           return "?";
    }
}

static void indent(int n) {
    while (n--) fputs("  ", stdout);
}

static void print_cmd(const t_cmd *c, int depth) {
    indent(depth);
    fputs("CMD:", stdout);
    for (size_t i = 0; c->argv && c->argv[i]; i++) {
        printf(" [%s]", c->argv[i]);
    }
    fputc('\n', stdout);

    for (const t_redir *r = c->redirs; r; r = r->next) {
        indent(depth + 1);
        printf("REDIR fd=%d %s %s\n", r->fd, redir_kind_str(r->kind), r->arg ? r->arg : "(null)");
    }
}

void ast_debug_print(const t_ast *node) {
    if (!node) { puts("(null)"); return; }
    if (node->kind == NODE_CMD) {
        print_cmd(&node->as.cmd, 0);
    } else {
        /* print as a tree: PIPE
           left subtree
           right subtree
        */
        puts("PIPE |");
        indent(1); puts("left:");
        if (node->as.pipe.left) {
            if (node->as.pipe.left->kind == NODE_CMD) print_cmd(&node->as.pipe.left->as.cmd, 2);
            else {
                indent(2); puts("(sub-pipe)");
                ast_debug_print(node->as.pipe.left);
            }
        }
        indent(1); puts("right:");
        if (node->as.pipe.right) {
            if (node->as.pipe.right->kind == NODE_CMD) print_cmd(&node->as.pipe.right->as.cmd, 2);
            else {
                indent(2); puts("(sub-pipe)");
                ast_debug_print(node->as.pipe.right);
            }
        }
    }
}


#include <stdio.h>

int main(void) {
    /* Example 1: echo hello > out.txt */
    char *echo_argv[] = { "echo", "hello", NULL };
    t_ast *n1 = ast_cmd_new(echo_argv);
    ast_cmd_add_redir(n1, R_OUT_TRUNC, 1, "out.txt");

    ast_debug_print(n1);
    ast_free(n1);

    /* Example 2: cat < in.txt | grep foo >> out.log */
    char *cat_argv[]  = { "cat", NULL };
    t_ast *cat = ast_cmd_new(cat_argv);
    ast_cmd_add_redir(cat, R_IN, 0, "in.txt");

    char *grep_argv[] = { "grep", "foo", NULL };
    t_ast *grep = ast_cmd_new(grep_argv);
    ast_cmd_add_redir(grep, R_OUT_APPEND, 1, "out.log");

    t_ast *pipe = ast_pipe_new(cat, grep);

    puts("\n--- pipeline ---");
    ast_debug_print(pipe);
    ast_free(pipe);

    /* Example 3: heredoc: cat << EOF | wc -l
       (executor should materialize heredoc into a pipe/tmp and connect to stdin)
    */
    char *cat2_argv[] = { "cat", NULL };
    t_ast *cat2 = ast_cmd_new(cat2_argv);
    ast_cmd_add_redir(cat2, R_HEREDOC, 0, "EOF");

    char *wc_argv[] = { "wc", "-l", NULL };
    t_ast *wc = ast_cmd_new(wc_argv);

    t_ast *p2 = ast_pipe_new(cat2, wc);
    puts("\n--- heredoc pipeline ---");
    ast_debug_print(p2);
    ast_free(p2);

    return 0;
}
