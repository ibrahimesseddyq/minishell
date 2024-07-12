#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h" 
#include <readline/readline.h>
#include <readline/history.h>



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

typedef struct s_status {
	int status;
	int st;
} t_st;

typedef struct s_lst {
	char *key;
	char *value;
	char sign;
	struct s_lst *next;
} t_lst;

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
		} block; // Added block member < file.txt cat
	};
} t_astnode;

char	*get_next_line(int fd);
void	exec_cmd_line(t_astnode *ast, t_st *st);
void	exec_cmd(t_astnode *ast, t_st *st);
void	exec_pip(t_astnode *ast);
void	exec_and(t_astnode *ast, t_st *st);
void	exec_or(t_astnode *ast, t_st *st);
char	*expand(char **key, char *the_env);
#endif