#include "./../minishell.h"

int my_exit(char **argv, int argc)
{
    long exit_value;

    if (argc > 2)
    {
        printf("minishell: exit: too many arguments\n");
        ft_exit(EXIT_FAILURE, EXIT_PROGRAM);
    }
    else
    {
        exit_value = atoi(argv[1]);
        if (exit_value > INT_MAX || exit_value < INT_MIN)
        {
            printf("minishell: exit: %s: numeric argument required\n", argv[1]);
            ft_exit(EXIT_FAILURE, EXIT_PROGRAM);
        }
        ft_exit(exit_value % 256, EXIT_PROGRAM);
    }
    return 1;
}
