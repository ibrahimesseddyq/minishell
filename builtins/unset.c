#include "./../minishell.h"

static int nb_args(char **args)
{
    int size;

    size = 0;
    while (args[size])
        size++;
    return (size);
}

int alpha_num(char c)
{
    if(c >= 'a' && c <= 'z')
        return (1);
    if(c >= 'A' && c <= 'Z')
        return (1);
    if(c == '_')
        return (1);
    if(c >= '0' && c <= '9')
        return (1);
    return (0);
}

int check_valid(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[0] >= '0' && str[0] <= '9' && i == 0)
            return (0);
        if (!alpha_num(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int unset(char **args, t_lst *lst)
{
    int i;

    i = 1;
    if (!args[1])
    {
        ft_exit(0, SET_EXIT_STATUS);
        return (1);
    }
    if (!check_valid(args[1]))
    {
        write(2,"valid identifier\n", 18);
        ft_exit(1, SET_EXIT_STATUS);
    }
    while ( i < nb_args(args))
    {
        set_env(lst,args[i], NULL, '=');
        i++;
    }
    if (ft_exit(1, GET_EXIT_STATUS) == 257)
        ft_exit(1, SET_EXIT_STATUS);
    return (1);
}