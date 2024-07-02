#include "../minishell.h"
#include "../frontend/frontend.h"


void exec_and(t_astnode *ast, t_st *st)
{
	exec_cmd_line(ast->binary.left, st);
	
	printf("[%d]\n", st->st);
	if (st->st == 0)
		exec_cmd_line(ast->binary.right, st);
}
