#include "../minishell.h"
#include "../frontend/frontend.h"
#include "minishell.h"

void exec_cmd_line(t_astnode *ast, t_st *st)
{
	if (ast->type == 0)
		exec_cmd(ast, st);
	else if (ast->type == 1)
		exec_pip(ast);
	else if (ast->type == 5)
		exec_and(ast, st);
	else if (ast->type == 6)
		exec_or(ast, st);

}
