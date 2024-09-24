#include "libft.h"

void    clean_fd()
{
    int i;

    i = 3;
    while (i < OPEN_MAX)
    {
        ft_close(&i);
        i++;
    }
}

int ft_close(int *fd)
{
    int ret;
    if (*fd < 0)
        return (0);
    ret = close(*fd);
    *fd = -1;
    return (ret);
}