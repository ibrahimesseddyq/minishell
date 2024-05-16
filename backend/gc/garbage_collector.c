#include "./../backend.h"

void gc_free(t_allocation *head)
{
    t_allocation *current = head;
    t_allocation *next;

    while (current != NULL)
	{
        next = current->next;

        if (!current->freed)
		{
            free(current->address);
            current->address = NULL;
            current->freed = 1;
        }
        if (current != head)
		{
            free(current);
        }

        current = next;
    }
    if (head != NULL && head->address == NULL)
	{
        free(head);
    }
}