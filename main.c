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
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void handle_sigterm(int num)
{
	(void)num;
	// printf("sigterm\n");
	exit(0);
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
	// signal(SIGQUIT, handle_sigterm);
	signal(SIGTERM, handle_sigterm);
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
			continue;
		if(t)
			add_history(t);
		token_list = tokenize(t);
		if (!analyse_syntax(token_list) && *t !='\0')
		{
			exit(0);
		}
		ast = parse_command_line(token_list);
		// if (!ast)
		// 	printf("ast is null, there is an error\n");
		token_list = tokenize(t);
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
