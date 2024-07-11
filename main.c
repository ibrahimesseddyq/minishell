#include "minishell.h"
#include "./frontend/frontend.h"

void f()
{
	system("leaks ./minishell");
}

int main(int ac, char **av, char *envp[]) {
	(void)ac;
	// (void)av;

	
	// t_tklist *token_list;
	// t_astnode *ast;
	// t_st st;
	// st.st = 0;
	// st.status = 0;

	// atexit(f);
	char	**env;
	int i;
	int	size;

	size = 0;
	env = NULL;
	i = 0;
	while (envp[size])
		size++;
	env = malloc(size * sizeof(char *));
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[size] = NULL;
   char *result = expand(env, av[1]);
    if (result)
        printf("%s\n", result);
    else
        printf("Key not found\n");
	// while (1)
	// {
	// 	char *t = readline("minishell:>$ ");
	// 	token_list = tokenize(t);
	// 	ast = parse_command_line(token_list);
	// 	if (!ast)
	// 		printf("ast is null, there is an error\n");
	// 	token_list = tokenize(t);
	// 	ast = parse_command_line(token_list);	
	// 	if (ast)
	// 	{
	// 		// expand();
	// 		// exec_cmd_line(ast, &st);
	// 	}
	// 	// printf("%d\n", st.st);
	// 	// print_ast(ast, 0);
	// }
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
