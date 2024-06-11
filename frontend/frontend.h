#ifndef FRONTEND_H
# define FRONTEND_H
// This is lexer
#include "./../minishell.h"
#include <ctype.h>
// Token types enumeration
typedef enum {
    TOKEN_EOF = 0,

    TK_LPR = 1,
    TK_RPR = 2,
    TK_AND = 3,
    TK_OR  = 4,
    TK_PIPE = 5,
    TK_LESSERTHAN1 = 6,
    TK_LESSERTHAN2 = 7,
    TK_GREATERTHAN1 = 8,
    TK_GREATERTHAN2 = 9,
    TK_WORD = 10,
    TK_ILLEGAL = -1,
    TK_COMMAND = 10,
    TK_SEMICOLON,
    TK_EQUAL,
    TK_PLUS,
    TK_MINUS
} tk_type;

// Define node types
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_INPUT_REDIRECT,
    NODE_OUTPUT_REDIRECT,
    NODE_SUBSHELL,
    NODE_LOGICAL_AND,
    NODE_LOGICAL_OR,
    NODE_SEQUENCE,
    NODE_BLOCK,
    NODE_REDIRECT_IN,
    NODE_REDIRECT_OUT,
    NODE_REDIRECT_APPEND,
    NODE_HEREDOC
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
    char *file;
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
t_astnode *parse_command_line(t_tklist *tokens);
t_astnode *parse_and_or(t_tklist *tokens, t_astnode *left, t_token *token);
t_astnode *parse_pipe(t_tklist *tokens);
t_astnode *parse_cmd(t_tklist *tokens);
void print_ast_node(t_astnode *node, int indent_level);
t_astnode *parse_block(t_tklist *tokens);
void print_ast(t_astnode *node, int depth);
t_tklist* tokenize(char *input);
void print_tokens(t_tklist *token_list);
int analyse_syntax(t_tklist *list);
void set_beginning(t_tklist *token_list);
#endif