#include "./../backend.h"
void *gcalloc(size_t size, t_allocation *lst)
{
    void *alloc = malloc(size);
    if (alloc == NULL)
        return NULL;

    if (lst->address == NULL) {
        lst->address = alloc;
        lst->freed = 0;
        lst->next = NULL;
        lst->prev = NULL;
    } else {
        while (lst->next != NULL)
		{
            lst = lst->next;
        }
        t_allocation *new_alloc = malloc(sizeof(t_allocation));
        if (new_alloc == NULL)
		{
            free(alloc);
            return NULL;
        }

        lst->next = new_alloc;
        new_alloc->prev = lst;
        new_alloc->address = alloc;
        new_alloc->freed = 0;
        new_alloc->next = NULL;
    }

    return alloc;
}