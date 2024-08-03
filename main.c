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
}

int main(int ac, char **av, char *env[]) {
	(void)ac;
	(void)av;
	(void)env;

	t_tklist *token_list;
	t_astnode *ast;
// <<<<<<< HEAD
	// t_st st;
	t_lst *lst;
	t_lst *tmp;
	// st.st = 0;
	// st.status = 0;
// =======
	t_st st;
	// t_lst *lst;
	st.st = 0;
	st.status = 0; 
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_catch_signals = 0;

	lst = envp(env);
	tmp = lst;
	while (1)
	{
		char *t = readline("minishell:>$ ");
		if (!t)
		{
			printf("exit\n");
			exit (1) ;
		}
		if(t)
			add_history(t);
		token_list = tokenize(t);

// <<<<	<<< HEAD
		// if (!analyse_syntax(token_list))
		// 	continue ;
// =======
		if (!analyse_syntax(token_list))
		{
			printf("Syntax Error\n");
			exit(1);
		}
// >>>>>>> 7a26dbad92025ab850bf7181e31863438fb69f7b
		set_beginning(token_list);
		ast = parse_command_line(token_list);	
		lst = tmp;
		// if (!lst)
		// 	printf("nop\n");
		if (!strcmp(ast->t_cmd.args[0], "env"))
		{
			while (lst)
			{
				printf("%s%c%s\n", lst->key, lst->signe, lst->value);
				lst = lst->next;
			}
		}
		else if (!strcmp(ast->t_cmd.args[0], "export"))
		{
			// set_env(lst , ast->t_cmd.args[1]);
			
		}
		
// <<<<<<< HEAD
		
// =======
		
// >>>>>>> 7a26dbad92025ab850bf7181e31863438fb69f7b
			// while (tmp)
			// {
			// 	printf("%s=%s\n", tmp->key, tmp->value);
			// 	tmp = tmp->next;
			// }
		if (ast)
		{
			// expand();
			// if (!strcmp(ast->t_cmd.args[0], "export"))
			// 	printf("export here \n");
			// else
			// print_ast(ast, 0);
			exec_cmd_line(ast, &st, lst);

		}
	}
	return 0;
}
