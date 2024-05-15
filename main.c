#include "minishell.h"
#include "./frontend/frontend.h"
int main(int ac, char **av)
{

	t_list *lst;
	lst = lex(add_spaces(">>>&"));
	test_lexer(lst);
	// printf("[%s]\n",add_spaces("ls > a >>> ( ls >& && || | ) ls"));
	// printf("[%s]",add_spaces("ls>a>>>(ls>&&&|||)ls"));

}