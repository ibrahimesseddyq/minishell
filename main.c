#include "minishell.h"
#include "./frontend/frontend.h"

void f()
{
	system("leaks ./minishell");
}

int main(int ac, char **av) {
	(void)ac;
	(void)av;

	t_tklist *token_list;
	t_astnode *ast;
	// atexit(f);
	while (1)
	{
		char *t = readline("minishell:>$ ");
		token_list = tokenize(t);
		ast = parse_command_line(token_list);
		if (!ast)
			printf("ast is null, there is an error\n");
		token_list = tokenize(t);
		ast = parse_command_line(token_list);
		if (ast)
		{
			exec_cmd_line(ast);
		}
		// print_ast(ast, 0);
	}
	// t_tklist *token_list = tokenize(av[1]);
	// if (!analyse_syntax(token_list))
	// {
	//     exit(0);
	// }
	// set_beginning(token_list);
	// t_astnode* ast = parse_command_line(token_list);
	// if (!ast)
	//     printf("ast is null, there is an error\n");
	// print_ast(ast, 0);
	return 0;
}
