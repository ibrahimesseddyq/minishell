#include "../minishell.h"
#include "../frontend/frontend.h"


void exec_and(t_astnode *ast)
{
    // (void)ast;
    printf("1-> %d\n", ast->t_cmd.st);
   
    // ast->binary.left->t_cmd.args[0];

    exec_cmd(ast->binary.left);
    // ast->t_cmd.status = 100;
    printf("2-> %d\n", ast->t_cmd.status);
    if (ast->t_cmd.st > 0)
    {
        printf("thats it 3-> %d\n", ast->t_cmd.status);
        exec_cmd(ast->binary.right);
    }
    else
    {
        printf("4-> %d\n", ast->t_cmd.status);
        printf("error\n");
    }
}
