#include "../minishell.h"
#include "../frontend/frontend.h"


void exec_and(t_astnode *ast)
{
    exec_cmd(ast->binary.left);
    if (ast->binary.left->t_cmd.st == 0)
        exec_cmd(ast->binary.right);
    else
    {
        printf("error\n");
        exit(1);
    }
}
