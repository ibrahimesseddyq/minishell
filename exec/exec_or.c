#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_or(t_astnode *ast)
{
	exec_cmd_line(ast->binary.left);
	if (ast->binary.left->t_cmd.st != 0)
		exec_cmd_line(ast->binary.right);
}
