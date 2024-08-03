#include "../minishell.h"

int ft_exit(int new_status, int mode)
{
    static int status = 0;
    if(mode == EXIT_PROGRAM)
        exit(status);
    else if(mode == GET_EXIT_STATUS)
        return status;
    else if (mode == SET_EXIT_STATUS)
        status = new_status;
    return status;
}