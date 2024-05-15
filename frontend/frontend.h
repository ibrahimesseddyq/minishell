#ifndef FRONTEND_H
# define FRONTEND_H
// This is lexer
#include "./../minishell.h"
typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_INPUT_REDIRECT,
    NODE_OUTPUT_REDIRECT,
    NODE_SUBSHELL
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
typedef enum {
		CMD, PIPE, REDIRECTION, LOGICAL, SEQUENCE, SUBSHELL
} node_type;


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
            struct ast_node* left;
            struct ast_node* right;
        } binary;

        struct
		{
            struct ast_node* child;
            char* filename;
            int mode;
        } redirect;

        struct
		{
            struct ast_node* child;
        } subshell;
    };
} t_astnode;
t_list *lex(char *text);
void test_lexer(t_list *lst);
char *add_spaces( char *str);
#endif