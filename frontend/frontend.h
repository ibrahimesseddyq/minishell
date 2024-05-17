#ifndef FRONTEND_H
# define FRONTEND_H
// This is lexer
#include "./../minishell.h"
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_INPUT_REDIRECT,
    NODE_OUTPUT_REDIRECT,
    NODE_SUBSHELL,
	NODE_LOGICAL,
    NODE_SEQUENCE,

} node_type;
typedef enum {
	TK_COMMAND,
	TK_PIPE,
	TK_SEMICOLON, // mamtlobach 
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
//12 3
typedef struct s_token
{
	tk_type type;
	char *value;
} t_token;
typedef struct	s_tklist
{
	t_list *tokens;
	int curr_index;
} t_tklist;
// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

typedef struct s_lexer
{
	char currentchar;
	int pos;
	char *input;
	char *charPos; //position for the next read 
} t_lexer;
// This is parser
// typedef enum {
// 		CMD, PIPE, REDIRECTION, LOGICAL, SEQUENCE, SUBSHELL
// } node_type;


typedef struct s_astnode
{
	node_type type;
    union {
        struct
		{
            char** argv;
            int argc;
        } cmd;

        struct
		{
            struct s_astnode* left;
            struct s_astnode* right;
        } binary;

        struct
		{
            struct s_astnode* child;
            char* filename;
            int mode;
        } redirect;

        struct
		{
            struct s_astnode* child;
        } subshell;
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
#endif