#include "./../backend.h"


#include <stdlib.h>


t_allocation **get_gc_list(void)
{
    static t_allocation *gc_list = NULL;
    return &gc_list;
}
int *how_many_allocated()
{
    static int alloc;
    return &alloc;
}
void *gcalloc(size_t size)
{
    t_allocation **list_ptr = get_gc_list();
    int *allocated = how_many_allocated();
    void *alloc = malloc(size);
    if (alloc == NULL)
        return NULL;

    t_allocation *new_node = malloc(sizeof(t_allocation));
    if (new_node == NULL)
    {
        free(alloc);
        return NULL;
    }
    (*allocated)++;
    new_node->address = alloc;
    new_node->freed = 0;
    new_node->next = *list_ptr;
    *list_ptr = new_node;

    return alloc;
}

void gc_free(void *ptr)
{
    t_allocation **list_ptr = get_gc_list();
    t_allocation *current = *list_ptr;
    t_allocation *prev = NULL;

    while (current != NULL)
    {
        if (current->address == ptr)
        {
            if (!current->freed)
            {
                free(current->address);
                current->freed = 1;
            }
            if (prev == NULL)
                *list_ptr = current->next;
            else
                prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void gc_free_all(void)
{
    t_allocation **list_ptr = get_gc_list();
    t_allocation *current = *list_ptr;
    t_allocation *next;
    int *allocated = how_many_allocated();
    int freed = 0;

    while (current != NULL)
    {
        next = current->next;
        if (!current->freed)
        {
            free(current->address);
        }
        free(current);
        freed++;
        current = next;
    }
    // printf("allocates %d\nfreed %d\n", *allocated,freed);
    *list_ptr = NULL;
}