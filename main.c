#include "minishell.h"
#include "./frontend/frontend.h"
int main(int ac, char **av)
{
	(void)av;
	(void)(ac);
	t_tklist *tklist;
	t_list *lst;
	t_astnode *root;

	tklist =malloc(sizeof(t_tklist));
	lst = lex(add_spaces("echo hello | grep h > file1.txt |  sort"));
	tklist->tokens = lst;
	tklist->curr_index = 0;
	root =parse_command_list(tklist);
	print_ast(root);
	// test_lexer(lst);
	// printf("[%s]\n",add_spaces("ls > a >>> ( ls >& && || | ) ls"));
	// printf("[%s]",add_spaces("ls>a>>>(ls>&&&|||)ls"));

}