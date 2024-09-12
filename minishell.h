#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h" 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <readline/readline.h>
#include <readline/history.h>

#define EXIT_PROGRAM 4
#define SET_EXIT_STATUS 2
#define GET_EXIT_STATUS 3
#define EXIT_FAIL 2
#define MNSH_PATH_MAX 4096
#define SUCCESS 1
#define FAILURE -1
#define IS_EXPORT 8

typedef struct stat t_stat;
typedef struct s_redir_islast
{
	int in_islast;
	int out_islast;
} t_redir_islast;

typedef enum
{
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
typedef enum
{
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
typedef struct s_token
{
	tk_type type;
	char *value;
} t_token;

// Token list structure
typedef struct s_tklist
{
	t_token *tokens;
	int curr_index;
	int size;
} t_tklist;

// Lexer structure
typedef struct s_lexer
{
	char currentchar;
	int pos;
	char *input;
} t_lexer;

// Redirection structure
typedef struct s_arg_node {
    char *arg;
    struct s_arg_node *next;
} t_arg_node;

typedef struct s_status {
	int status;
	int st;
} t_st;

// AST node structure
typedef struct s_astnode {
	node_type type;
	union {
		struct s_cmd {
			char *cmd;
			t_arg_node *args;
			int args_size;
    		t_redir_list *redirections;
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
		} block;
	};
} t_astnode;

char	*get_next_line(int fd);
pid_t exec_cmd_line(t_astnode *ast, t_lst *env);
int		exec_cmd(t_astnode *ast, t_lst *env);
void	exec_pip(t_astnode *ast, t_lst *env);
pid_t	exec_and(t_astnode *ast, t_lst *env);
pid_t	exec_or(t_astnode *ast, t_lst *env);
t_lst	*envp(char **env);
char	*get_env(t_lst *env, char *the_env);
void	set_env(t_lst *lst, char *key, char *new_value, int sign);
int	ft_red_in(t_astnode *ast, t_lst *env, int is_last);
int		ft_red_out(t_astnode *ast, t_lst *env, int is_last);
int	ft_redirection(t_astnode *ast, t_lst *env);
char	*ft_expand(char *line, t_lst *env);
int		ft_cd(int argc, char **argv, int mode, t_lst *env);
char	*ft_pwd(void);
int		ft_exit(int status, int mode);
int		ft_echo(char **args);
void	ft_env(t_lst *env_list);
int my_exit(char **argv, int argc);
void ft_export(char **str, t_lst *lst);
void gc_free_all(void);
char	**ft_split_quotes(char const *s, char c);
 char which_to_split_with( char **strs, int index);
 char *get_splitted_char(int index);
 char **split_all_strings(char **array, char delimiter);
char *ft_expand_redir(char *line, t_lst *env);

char *ft_expand_heredoc(char *line, t_lst *env);
int unset(char **args, t_lst *lst);
void append_env(t_lst *lst, char *key, char *new_value);
int get_env_isset(t_lst *env, char *the_env);
#endif