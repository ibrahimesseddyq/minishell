
#include "libft.h"

pid_t   ft_fork()
{
    pid_t ret;

    ret = fork();
    if (ret < 0)
        exit(1);
    return (ret);
}