#include "./../minishell.h"

int unset(char **args, t_lst *lst)
{
    if (!args[1])
    {
        printf("minishell: unset: too few arguments\n");
        ft_exit(2, SET_EXIT_STATUS);
        return 0;
    }
    for (int i = 1; i < args_size; i++)
    {
            set_env(lst,args[i], "");
    }
    return 1;
}