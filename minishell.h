/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 03:48:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 08:12:13 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h" 
# include <sys/types.h> 
# include <sys/wait.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdio.h>
# include <termios.h>
# include <signal.h>

# define EXIT_FAIL 2
# define EXIT_SUCCESS 0
# define NO_EXIT 0
# define SECURE_PATH "/"
# define EXIT_PROGRAM 4
# define SET_EXIT_STATUS 2
# define GET_EXIT_STATUS 3
# define UNSET_BUILTIN 4
# define EXPORT_BUILTIN 2
# define CD_BUILTIN 3
# define EXIT_FAIL 2
# define MNSH_PATH_MAX 4096
# define SUCCESS 1
# define FAILURE -1
# define IS_EXPORT 8
# define INITIAL_ARRAY_SIZE 10
# define ARRAY_INCREMENT 10
# define WORD ".[]-_\"\'$#@/*+=^"
# define INITIAL_BUFFER_SIZE 256
# define BUFFER_GROWTH_FACTOR 2
# define SET_BUILTIN 1
# define GET_BUILTIN 2
# define ACTIVE 1
# define INACTIVE 0
# define UNKNOWN -1
# define ROWS 9
# define COLS 11
# define GET_AST 2
# define SET_AST 1

extern int				g_sig_var;
typedef int				(*matrix)[11];
typedef struct s_stat	t_stat;
typedef struct s_redir_islast
{
	int	in_islast;
	int	out_islast;
}	t_redir_islast;

typedef enum e_type
{
	TOKEN_EOF = 0,
	TK_LPR = 1,
	TK_RPR = 2,
	TK_AND = 3,
	TK_OR = 4,
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
}	t_type;

typedef struct s_wildcard_data
{
	char		**pattern;
	int			levels;
	char		***found_files;
	int			*found_count;
	struct stat	st;
}	t_wildcard_data;

typedef enum e_node_type
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
}	t_node_type;

typedef struct s_allocation
{
	void				*address;
	int					freed;
	struct s_allocation	*next;
}	t_allocation;

typedef struct s_token
{
	t_type	type;
	char	*value;
}	t_token;

typedef struct s_tklist
{
	t_token	*tokens;
	int		curr_index;
	int		size;
}	t_tklist;

typedef struct s_lexer
{
	char	currentchar;
	int		pos;
	char	*input;
}	t_lexer;

typedef struct s_arg_node
{
	char				*arg;
	struct s_arg_node	*next;
}	t_arg_node;

typedef struct s_status
{
	int	status;
	int	st;
}	t_st;

typedef struct s_quote_state
{
	int		in_quotes;
	char	quote_char;
}	t_quote_state;

typedef struct s_heredoc_data
{
	char	*delimiter;
	char	*non_expanded_delimiter;
	int		fd_rd;
	int		fd;
	t_lst	*env;
	char	*filename;
}	t_heredoc_data;

typedef struct s_state
{
	int			i;
	int			star_inside;
	char		*expanded_string;
	char		**splitted_args;
	char		*expanded_arg;
	char		*temp;
	t_arg_node	*lst;
	t_arg_node	*head;
}	t_state_fs;

typedef struct s_astnode
{
	t_node_type	type;
	union
	{
		struct s_cmd
		{
			char			*cmd;
			t_arg_node		*args;
			int				args_size;
			t_redir_list	*redirections;
			int				flag_infiles;
			int				flag_outfiles;
		}	t_cmd;
		struct s_binary
		{
			struct s_astnode	*left;
			struct s_astnode	*right;
		}	t_binary;
		struct s_redirect
		{
			struct s_astnode	*child;
			char				*filename;
			int					mode;
		}	t_redirect;
		struct s_block
		{
			struct s_astnode	*child;
		}	t_block;
	};
}	t_astnode;

typedef struct s_expand_params
{
	int		i;
	int		expanded_size;
	int		expanded_index;
	int		is_inside_quotes;
	char	current_quote;
	char	*expanded_line;
	int		is_inside_quotes2;
	int		is_inside_quotes3;
}	t_expand_params;

typedef struct s_wildcard_redir_res
{
	char	*expanded_result;
	int		size;
}	t_wd_redir_res;

typedef struct s_pipeline
{
	int	pid;
	int	read_fd;
	int	write_fd;
}	t_pipeline;

void			exec_cmd_line(t_astnode *ast, t_lst *env);
int				exec_cmd(t_astnode *ast, t_lst *env);
void			exec_pip(t_astnode *ast, t_lst *env);
void			exec_and(t_astnode *ast, t_lst *env);
void			exec_or(t_astnode *ast, t_lst *env);
t_lst			*envp(char **env);
char			*get_env(t_lst *env, char *the_env);
void			set_env(t_lst *lst, char *key, char *new_value, int sign);
int				ft_red_in(t_astnode *ast,
					t_lst *env, int is_last, int command_exist);
int				ft_red_out(t_astnode *ast, t_lst *env,
					int is_last, int command_exist);
int				ft_redirection(t_astnode *ast, t_lst *env, int command_exist);
char			*ft_expand(char *line, t_lst *env, char *cmd);
int				ft_cd(int argc, char **argv, t_lst *env);
char			*ft_pwd(t_lst *env);
int				ft_exit(int status, int mode);
int				ft_echo(char **args);
void			ft_env(t_lst *env_list);
int				my_exit(char **argv, int argc);
void			ft_export(char **str, t_lst *lst);
void			gc_free_all(void);
char			**ft_split_quotes(char const *s, char c);
char			which_to_split_with( char **strs, int index);
char			*get_splitted_char(int index);
char			**split_all_strings(char **array, char delimiter);
char			*ft_expand_redir(char *line, t_lst *env);
int				count_env_vars(t_lst *env);
char			*ft_expand_heredoc(char *line, t_lst *env);
int				unset(char **args, t_lst *lst);
void			append_env(t_lst *lst, char *key, char *new_value);
int				get_env_isset(t_lst *env, char *the_env);
char			*ft_expand_delimiter(char *line);
t_arg_node		*get_node_at(t_arg_node *lst, int pos);
char			**list_to_array(t_arg_node *lst, t_astnode *ast);
char			*find_command_in_path(const char *cmd, char **path_dirs);
int				execute_child(char **arg_cmd, t_astnode *ast, t_lst *env);
char			**make_array(char **args, int size);
int				no_command_case(t_arg_node **lst, t_lst *env, t_astnode *ast);
char			*char_to_string(char c);
int				is_builtin_command(const char *cmd);
int				execute_builtin(char **arg_cmd, t_astnode *ast, t_lst *env);
int				initial_builtin_errors(t_arg_node *args);
char			*check_if_in_paths(char *cmd, t_lst *env);
char			*get_splitted_char(int index);
void			set_splitted_char(char c, int index);
int				is_relative_absolute(const char *path);
char			**build_envp(t_lst *env);
void			handle_exec_error(void);
char			*check_file(char **argv, t_lst *env);	
t_expand_params	init_params(char *expanded_line);
t_token			*get_next_token(t_lexer *lexer);
t_token			*next_token(t_tklist *token_list);
int				heredoc_delimiter_valid(char *del);
int				write_heredoc_to_file(char *delimiter,
					char *filename, t_lst *env, int *fd_rd);
t_token			*peek_token(t_tklist *token_list);
int				heredoc_delimiter_valid(char *del);
t_astnode		*create_ast_command(int ac, char **av);
t_lst			*choose_add_set_env(char *key, char *new_value, int sign);
void			print_export(t_lst *lst);
void			export_var(char **str, t_lst *lst, int i);
int				get_var_length(char *line, int i);
void			append_string(t_expand_params *params, char *str);
void			expand_exit_status(t_expand_params *params);
int				handle_quotes2(char c, t_expand_params *params, char *line);
void			append_char(t_expand_params *params, char c);
int				check_ambigious(char *str);
t_tklist		*tokenize(char *input);
int				analyse_syntax(t_tklist *list);
void			set_beginning(t_tklist *token_list);
t_astnode		*parse_command_line(t_tklist *tokens, t_lst *lst);
t_astnode		*parse_cmd(t_tklist *tokens, t_lst *lst);
t_astnode		*create_binary_node(t_node_type type,
					t_astnode *left, t_astnode *right);
t_astnode		*create_block_node(t_astnode *child);
t_astnode		*parse_block(t_tklist *tokens, t_lst *lst);
bool			is_valid_quotes(const char *str);
int				there_is_quote(char *str);
char			*allocate_buffer(size_t buffer_size);
char			*resize_buffer(char *buffer, size_t *buffer_size);
int				handle_escaped_characters(t_lexer *lexer,
					char *result, size_t *i);
int				should_stop(t_lexer *lexer, int in_quotes);
void			advance(t_lexer *lexer);
char			*finalize_buffer(char *buffer, size_t i);
int				handle_quotes(t_lexer *lexer,
					t_quote_state *quote_state, char *result, size_t *i);
char			*get_word(t_lexer *lexer);
void			skip_whitespace(t_lexer *lexer);
t_token			*token_and(t_lexer *lexer);
t_token			*token_opening_parenthesis(t_lexer *lexer);
t_token			*token_r_redir(t_lexer *lexer);
t_token			*token_pipe(t_lexer *lexer);
char			*trim_quotes(char *str);
int				get_symbol_exist(char *str, char symbol);
void			apppend_to_var(t_export_var *state, char *str, t_lst *lst);
void			expand_token_heredoc(t_expand_params *params,
					t_lst *env, char **line);
void			expand_variable_heredoc(t_expand_params *params,
					t_lst *env, char **line);
void			expand_variable(t_expand_params *params,
					t_lst *env, char **line, int export_case);
int				expand_token(t_expand_params *params,
					t_lst *env, char **line, char *cmd);
void			gc_free(void *ptr);
int				match(char *pattern, const char *text);
void			handle_overflow(void);
int				execute_external(char **arg_cmd, t_astnode *ast, t_lst *env);
int				check_valid(char *str);
void			handle_sig(int sig);
char			*expand_wildcard(char *pwd, int level, t_wildcard_data *data);
char			*ft_strcpy(char *s1, char *s2);
char			*ft_strcat(char *dest, char *src);
char			*expand_wd(char *expanded_arg);
int				handle_ambiguous(char *str);
t_list			**get_heredoc_list(void);
int				ft_sprintf(char *str, const char *format, int num);
t_wd_redir_res	*expand_wildcard_redir(char *pwd,
					int level, t_wildcard_data *data);
int				check_valid_export(char *str);
int				check_valid_unset(char *str);
t_token			*token_closing_parenthesis(t_lexer *lexer);
void			initialize(t_tklist **token_list, t_astnode	**ast);
int				valid_quotes_main(char *line);
void			handle_sig(int sig);
void			ft_handler(int sig);
int				heredoc_delimiter_valid(char *del);
int				write_expanded_line(char *delimiter,
					char *line, int fd, t_lst *env);
void			initialize_analyzer(char **final_token,
					int *parenthesis, t_token **tk, int *e);
int				special_cases(char *cmd, t_lst *env, t_astnode *ast);

char			*get_expanded_string(t_lst *env, t_arg_node *lst, char *cmd);
char			**filterstrings(char *pattern,
					char *texts[], int numTexts, int *numMatches);
int				ft_isspace(char c);
void			choose_splitting_delimiter(t_arg_node	*lst, t_astnode *ast);
char			**get_files(const char *dir,
					int *numFiles, t_wildcard_data *data);
char			*ft_expand_tilde(char *path, t_lst *env);
void			wildcard2(const char *pwd, int level,
					t_wildcard_data *data, t_wd_redir_res *res);
void			add_to_found(char ***found_files,
					int *found_count, const char *file);
t_wd_redir_res	*expand_wd_redir(char *expanded_arg);
int				slash_exist(char *str);
int				is_not_a_charachter(char c);
void			remove_ampersand_strings(char **arr, int *size);
char			*skip_char(const char *input, char skip);
char			*get_empty_str(void);
char			*replace_star_outside_quotes(const char *input);
char			*handle_ambiguous_wd(t_redir *redir);
int				append_dollar_redir(t_expand_params *params, char **line);
matrix			get_matrix(void);
char			*alloc_del(void);
char			**generate_final_splitted(t_astnode *ast,
					t_lst *env, t_arg_node *lst);
void			mark_file_as_found(t_wildcard_data *data,
					char	**validpaths, int *i);
int				is_valid_file(char *filename, t_wildcard_data *data);
void			bubble_sort(char **arr, int n);
char			*replace_space_with_second_separator(t_expand_params *params,
					char *str);
int				is_quote(char c);
char			*get_null_str(void);
void			handle_setting_var(char *str, t_export_var *state, t_lst *lst);
char			*make_filename(char *file);
int				contains_just(char *str, char c);
int				next_empty_string(char *line,
					t_expand_params *params, char quote);
char			*make_empty_and_null(char *str);
int				handle_translation(t_expand_params *params,
					t_lst *env, char **line, int *quote_export);
int				*return_array_of_2(int a, int b);
int				handle_export_case(char **line, char *cmd);
int				expand_after_dollar_redir(t_expand_params *params,
					t_lst *env, char **line);
int				star_not_inside_quotes(const char *str);
void			add_to_found_2(char ***found_files,
					int *found_count, const char *file);

void			print_redirection(t_redir_list *redir_list,
					const char *type, int depth);
void			print_ast(t_astnode *node, int depth);
int				is_a_redir_in(t_astnode *ast);
void			close_heredoc_fds(t_astnode *ast);
void			close_command_heredocs(t_astnode *cmd);
int				check_and_open_file(const char *file, int flags, mode_t mode);
int				*get_last_redirs(t_astnode *ast);
int				check_error_redir_out(t_redir *redir);
int				check_if_directory(char *cmd);
char			*trim_spaces(char *str);
t_astnode		*get_ast(t_astnode *ast, int mode);
void			close_all_heredoc_fds(t_astnode *ast);
char			*check_file(char **argv, t_lst *env);
char			*check_file_with_path(char *cmd, t_lst *env);
char			*check_file_no_path(char *cmd);
void			is_directory_error(void);
int				is_directory(char *cmd);
void			handle_sigint(int sig);
void			restore_signal_handlers(void);
int				check_dir_exist(char *path);
void	close_heredocs(void);
void	add_heredoc_fd_to_list(int *fd);
#endif