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

int ft_echo(char **args)
{
    int i = 1;
    bool n_option = false;

    if (nb_args(args) > 1)
    {
        // Check for -n option(s)
        while (args[i] && ft_strcmp(args[i], "-n") == 0)
        {
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