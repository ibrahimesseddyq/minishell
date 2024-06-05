#ifndef FRONTEND_H
# define FRONTEND_H
// This is lexer
#include "./../minishell.h"
#include <ctype.h>
// Token types enumeration
typedef enum {
    TK_COMMAND,
    TK_PIPE,
    TK_SEMICOLON,
    TK_LPR,
    TK_RPR,
    TK_ILLEGAL,
    TOKEN_EOF,
    TK_AND1,
    TK_AND2,
    TK_GREATERTHAN1,
    TK_GREATERTHAN2,
    TK_LESSERTHAN2,
    TK_LESSERTHAN1,
    TK_WORD,
    TK_EQUAL,
    TK_PLUS,
    TK_OR,
    TK_MINUS
} tk_type;

// Define node types
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_INPUT_REDIRECT,
    NODE_OUTPUT_REDIRECT,
    NODE_SUBSHELL,
    NODE_LOGICAL,
    NODE_SEQUENCE,
    NODE_BLOCK
} node_type;

// Token structure
typedef struct s_token {
    tk_type type;
    char *value;
} t_token;

// Token list structure
typedef struct s_tklist {
    t_token *tokens;
    int curr_index;
    int size;
} t_tklist;

// Lexer structure
typedef struct s_lexer {
    char currentchar;
    int pos;
    char *input;
} t_lexer;

// Redirection structure
typedef struct s_redir {
    char **file;
    char *heredoc;
    int type;
    int number;
} t_redir;

// AST node structure
typedef struct s_astnode {
    node_type type;
    union {
        struct s_cmd {
            char *cmd;
            char **args;
            t_redir *infile;
            t_redir *outfile;
            t_redir *heredoc;
            t_redir *append;
            int flag_infiles;
            int flag_outfiles;
        } t_cmd;

        struct {
            struct s_astnode* left;
            struct s_astnode* right;
        } binary;

        struct {
            struct s_astnode* child;
            char* filename;
            int mode;
        } redirect;

        struct {
            struct s_astnode* child;
        } subshell;

        struct {
            struct s_astnode* child;
        } block; // Added block member
    };
} t_astnode;
t_list *lex(char *text);
void test_lexer(t_list *lst);
char *add_spaces( char *str);
 t_token *peek_next_token(t_tklist *token_list, int n);
  t_token *next_token(t_tklist *token_list);
    t_token *peek_token(t_tklist *token_list);
	t_astnode* parse_pipeline(t_tklist *token_list, t_token **current_token);
t_astnode* parse_subshell(t_tklist *token_list, t_token **current_token);
t_astnode* parse_logical_expression(t_tklist *token_list, t_token **current_token);
t_astnode* parse_sequence(t_tklist *token_list, t_token **current_token);
t_astnode* parse_command_list(t_tklist *token_list);
void print_ast_node(t_astnode *node, int indent_level);
void print_ast(t_astnode *root);
t_tklist* tokenize(char *input);
void print_tokens(t_tklist *token_list);
#endif