#include "./../minishell.h"
static int nb_args(char **args)
{
    int size = 0;
    while (args[size])
        size++;
    return (size);
}
int unset(char **args, t_lst *lst)
{
    if (!args[1])
    {
        printf("minishell: unset: too few arguments\n");
        ft_exit(2, SET_EXIT_STATUS);
        return 0;
    }
    for (int i = 1; i < nb_args(args); i++)
    {
            set_env(lst,args[i], NULL, '=');
    }
    return 1;
}