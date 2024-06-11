#include "minishell.h"
#include "./frontend/frontend.h"

int main(int ac, char **av) {
    (void)ac;
    t_tklist *token_list = tokenize(av[1]);
    t_astnode* ast = parse_command_line(token_list);
    if (!ast)
        printf("ast is null, there is an error\n");
    print_ast(ast, 0);
    return 0;
}

