#ifndef FRONTEND_H
# define FRONTEND_H
// This is lexer
#include "./../minishell.h"
#include <ctype.h>





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