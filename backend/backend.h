#ifndef BACKEND_H
# define BACKEND_H
#include <stdlib.h>

typedef struct s_allocation
{
	int freed;
	void *address;
	struct s_allocation *prev;
	struct s_allocation *next;
} t_allocation;
void *gcalloc(size_t size, t_allocation *lst);
void	initialize_gc(t_allocation *root);
void gc_free(t_allocation *head);
#endif