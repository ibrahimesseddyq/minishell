#include <stdio.h>
#include <string.h>
#include "./../minishell.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>


static int nb_args(char **args)
{
    int size = 0;
    while (args[size])
        size++;
    return (size);
}
int check_just_n(char *arg)
{
    int i;

    i = 0;
    while(arg[i])
    {
        if(arg[i] != 'n') 
            return (0);
        i++;
    }
    return (1);

}
int ft_echo(char **args)
{
    int i = 1;
    bool n_option = false;
    // for(int i = 0; args[i]; i++)
    // {
    //     printf("args[%d] = %s\n", i, args[i]);
    // }
    if (nb_args(args) > 1)
    {
        // Check for -n option(s)
        while (args[i] && ft_strncmp(args[i], "-", 1) == 0)
        {
            if(!check_just_n(args[i] + 1))
                break;
            n_option = true;
            i++;
        }

        // Print arguments
        while (args[i])
        {
            write(1, args[i], strlen(args[i]));
            if (args[i + 1])
                write(1, " ", 1);
            i++;
        }
    }

    // Print newline if -n option is not present
    if (!n_option)
        write(1, "\n", 1);

    return (SUCCESS);
}