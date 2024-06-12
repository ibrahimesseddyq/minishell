#include "minishell.h"
#include "./frontend/frontend.h"

int main(int ac, char **av) {
    (void)ac;
    (void)av;

    t_tklist *token_list;
    t_astnode *ast;

    while (1)
    {
        char *t = readline("minishell:>$ ");
        token_list = tokenize(t);
        ast = parse_command_line(token_list);
        if (!ast)
            printf("ast is null, there is an error\n");
        if (ast->type == 0)
        {   
            // execve(ast->t_cmd.args[0]);
            printf("cmd------------------> %s\n", ast->t_cmd.args[0]);
        }
        if (ast->type == 1)
        {   
            // execve(ast->t_cmd.args[0],);
            printf("cmd------------------> %s\n", ast->t_cmd.args[0]);
        }
        // if (ast->type == 1)
        // {
        //     printf("pip------------------>\n");
        // }
        // print_ast(ast, 0);
    }

    return 0;
}
