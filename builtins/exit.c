#include "./../minishell.h"
int ft_isnum(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}
int check_error_exist(char *str)
{
    int i;

    i = 0;
    if(str[i] == '-' || str[i] == '+')
        i++;
    while(str[i])
    {
        if(!ft_isnum(str[i]))
            return (1);
        i++;
    }
    return (0);
}
int my_exit(char **argv, int argc)
{
    long exit_value;
    int error_exist;

    error_exist = 0;

    if (argc > 2)
    {
        printf("minishell: exit: too many arguments\n");
        ft_exit(EXIT_FAILURE, SET_EXIT_STATUS);
        return (0);
    }
    else
    {
        error_exist = check_error_exist(argv[1]);
        exit_value = atoi(argv[1]);
        if (exit_value > INT_MAX || exit_value < INT_MIN || error_exist)
        {
            printf("minishell: exit: %s: numeric argument required\n", argv[1]);
            ft_exit(255, SET_EXIT_STATUS);
            return (0);
        }
        else
            ft_exit(exit_value % 256, EXIT_PROGRAM);
    }
    return 1;
}
