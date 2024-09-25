
#include "libft.h"

char *ft_getcwd(char *buf, size_t size)
{
    char    *ret;

    ret = getcwd(buf, size);
    if (!ret)
        exit(1);
    return (ret);
}