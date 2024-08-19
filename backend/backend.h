#ifndef BACKEND_H
# define BACKEND_H
#include <stdlib.h>
#include "./../minishell.h"

typedef struct s_allocation
{
    void *address;
    int freed;
    struct s_allocation *next;
} t_allocation;

void gc_free(void *ptr);
#endif