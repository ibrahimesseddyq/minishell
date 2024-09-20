#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h" 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>
#include <glob.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define EXIT_FAIL 2
#define EXIT_SUCCESS 0
#define NO_EXIT 0
#define EXIT_PROGRAM 4
#define SET_EXIT_STATUS 2
#define GET_EXIT_STATUS 3
#define EXIT_FAIL 2
#define MNSH_PATH_MAX 4096
#define SUCCESS 1
#define FAILURE -1
#define IS_EXPORT 8
#define INITIAL_ARRAY_SIZE 10
#define ARRAY_INCREMENT 10
#define WORD ".[]\\-_\"\'&$/*+;="
#define INITIAL_BUFFER_SIZE 256
#define BUFFER_GROWTH_FACTOR 2

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
typedef struct s_wildcard_data
{
    char **pattern;
    int levels;
    char ***found_files;
    int *found_count;
	struct stat st;
} t_wildcard_data;

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

typedef struct s_allocation
{
    void *address;
    int freed;
    struct s_allocation *next;
} t_allocation;

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

typedef struct s_quote_state {
    int  in_quotes;
    char quote_char;
} t_quote_state;

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

typedef struct s_expand_params
{
    int i;
    int expanded_size;
    int expanded_index;
    int is_inside_quotes;
    char current_quote;
    char *expanded_line;
    int is_inside_quotes2;
} t_expand_params;

char	*get_next_line(int fd);
void exec_cmd_line(t_astnode *ast, t_lst *env);
int		exec_cmd(t_astnode *ast, t_lst *env);
void	exec_pip(t_astnode *ast, t_lst *env);
void	exec_and(t_astnode *ast, t_lst *env);
void	exec_or(t_astnode *ast, t_lst *env);
t_lst	*envp(char **env);
char	*get_env(t_lst *env, char *the_env);
void	set_env(t_lst *lst, char *key, char *new_value, int sign);
int	ft_red_in(t_astnode *ast, t_lst *env, int is_last, int command_exist);
int ft_red_out(t_astnode *ast, t_lst *env, int is_last, int command_exist);
int	ft_redirection(t_astnode *ast, t_lst *env, int command_exist);
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
int	count_env_vars(t_lst *env);

char *ft_expand_heredoc(char *line, t_lst *env);
int unset(char **args, t_lst *lst);
void append_env(t_lst *lst, char *key, char *new_value);
int get_env_isset(t_lst *env, char *the_env);
char *ft_expand_delimiter(char *line, t_lst *env);

t_arg_node	*get_node_at(t_arg_node *lst, int pos);
char **list_to_array(t_arg_node *lst);
char *find_command_in_path(const char *cmd, char **path_dirs);
int execute_external(char **arg_cmd, t_astnode *ast, t_lst *env);
void expand_arguments(t_astnode *ast, t_lst *env);
char **make_array(char **args, int size);
int builtins_error(char **argv);
int special_cases( t_arg_node *lst);
int no_command_case(t_arg_node *lst, t_lst *env, t_astnode *ast);
char	*char_to_string(char c);
int	is_builtin_command(const char *cmd);
int	execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env);
int	initial_builtin_errors(t_arg_node *args);
char	*arg_cmds(char *cmd, t_lst *env);
char	*get_splitted_char(int index);
void    set_splitted_char(char c, int index);
const int	is_relative_absolute(const char *path);
char	**build_envp(t_lst *env);
void	handle_exec_error(const char *cmd);
int	count_args(char **args);
int	check_file(char **argv);
int	check_export_errors(char *str);
t_expand_params	init_params(char *line, char *expanded_line);
t_token	*get_next_token(t_lexer *lexer);
t_token	*next_token(t_tklist *token_list);
int	heredoc_delimiter_valid(char *del);
int	write_heredoc_to_file(const char *delimiter, char *filename, t_lst *env);
t_token	*peek_token(t_tklist *token_list);
int	heredoc_delimiter_valid(char *del);
t_astnode	*create_ast_command(int ac, char **av);
t_lst	*choose_add_set_env(char *key, char *new_value, int sign);
void	print_export(t_lst *lst);
void	export_var(char **str, t_lst *lst, int i);
int	get_var_length(char *line, int i);
void	append_string(t_expand_params *params, char *str);
void	expand_exit_status(t_expand_params *params);
int	append_char_to_string(char **s, char c);
int	handle_quotes2(char c, t_expand_params *params);
void	append_char(t_expand_params *params, char c);
int	check_ambigious(char *str);
t_tklist	*tokenize(char *input);
int	analyse_syntax(t_tklist *list);
void	set_beginning(t_tklist *token_list);
t_astnode	*parse_command_line(t_tklist *tokens, t_lst *lst);
t_astnode	*parse_cmd(t_tklist *tokens, t_lst *lst);
t_astnode	*create_binary_node(node_type type
		, t_astnode *left, t_astnode *right);
t_astnode	*create_block_node(t_astnode *child);
t_astnode	*parse_block(t_tklist *tokens, t_lst *lst);
bool	is_valid_quotes(const char *str);
int	there_is_quote(char *str);
char	*allocate_buffer(size_t buffer_size);
char	*resize_buffer(char *buffer, size_t *buffer_size);
int	handle_escaped_characters(t_lexer *lexer, char *result, size_t *i);
int	should_stop(t_lexer *lexer, int in_quotes);
void	advance(t_lexer *lexer);
char	*finalize_buffer(char *buffer, size_t i);
int	handle_quotes(t_lexer *lexer
	, t_quote_state *quote_state, char *result, size_t *i);
	char	*get_word(t_lexer *lexer);
	void	skip_whitespace(t_lexer *lexer);
	t_token	*token_and(t_lexer *lexer);
	t_token	*token_opening_parenthesis(t_lexer *lexer);
	t_token	*token_r_redir(t_lexer *lexer);
	t_token	*token_pipe(t_lexer *lexer);
char	*trim_quotes(char *str);
int	get_symbol_exist(char *str, char symbol);
void	apppend_to_var(char **key, char **value,
		char **temp, char *str, t_lst *lst);
void	expand_token_heredoc(t_expand_params *params, t_lst *env, char *line);
void	expand_variable_heredoc(t_expand_params *params, t_lst *env, char *line);
void	expand_variable(t_expand_params *params, t_lst *env, char **line);
void	expand_token(t_expand_params *params, t_lst *env, char **line);
void gc_free(void *ptr);
bool matchStar(char ch, const char *pattern, const char *text);
bool match(const char *pattern, const char *text);
char** filterStrings(const char *pattern, const char *texts[], int numTexts, int *numMatches);
char **remove_empty_strings(char **arr, int size, int *new_size);
// t_list *lex(char *text);
// void test_lexer(t_list *lst);
// char *add_spaces( char *str);
//  t_token *peek_next_token(t_tklist *token_list, int n);
//   t_token *next_token(t_tklist *token_list);
//     t_token *peek_token(t_tklist *token_list);
// 	t_astnode* parse_pipeline(t_tklist *token_list, t_token **current_token);
// t_astnode* parse_subshell(t_tklist *token_list, t_token **current_token);
// t_astnode* parse_logical_expression(t_tklist *token_list, t_token **current_token);
// t_astnode* parse_sequence(t_tklist *token_list, t_token **current_token);
// t_astnode* parse_command_list(t_tklist *token_list);
// t_astnode *parse_command_line(t_tklist *tokens, t_lst *lst);
// t_astnode *parse_and_or(t_tklist *tokens, t_astnode *left, t_token *token, t_lst *lst);
// t_astnode *parse_pipe(t_tklist *tokens, t_lst *lst);
// t_astnode *parse_cmd(t_tklist *tokens, t_lst *lst);
// void print_ast_node(t_astnode *node, int indent_level);
// t_astnode *parse_block(t_tklist *tokens, t_lst *lst);
// void print_ast(t_astnode *node, int depth);
// t_tklist* tokenize(char *input);
// void print_tokens(t_tklist *token_list);
// int analyse_syntax(t_tklist *list);
// void set_beginning(t_tklist *token_list);
#endif