#include "minishell.h"
#include "./frontend/frontend.h"
#include <signal.h>

void f()
{
	// system("leaks ./minishell");
}
void handle_sigint(int num)
{
	(void)num;
	printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
	// rl_catch_signals = 0;


}

int main(int ac, char **av, char *envp[]) {
	(void)ac;
	(void)av;
	(void)envp;
	
	t_tklist *token_list;
	t_astnode *ast;
	t_st st;
	// t_lst lst;
	st.st = 0;
	st.status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_catch_signals = 0;
// 	atexit(f);
// 	char	**env;
// 	int i;
// 	int	size;

// 	size = 0;
// 	env = NULL;
// 	i = 0;
// 	while (envp[size])
// 		size++;
// 	env = malloc(size * sizeof(char *));
// 	while (envp[i])
// 	{
// 		env[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	env[size] = NULL;
//    char *result = expand(env, av[1]);
// 	if (result)
// 		printf("%s\n", result);
// 	else
// 		printf("Key not found\n");




// the first main();

	while (1)
	{
		char *t = readline("minishell:>$ ");
		if (!t)
		{
			printf("exit\n");
			exit(0);
		}
		if(t)
			add_history(t);
		token_list = tokenize(t);
		// if (!analyse_syntax(token_list))
		// {
		// 	exit(0);
		// }
		ast = parse_command_line(token_list);
		if (ast)
		{
			// expand();
			exec_cmd_line(ast, &st);
			// print_ast(ast, 0);
		}
	}
	return 0;
}
