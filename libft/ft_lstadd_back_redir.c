#include "libft.h"


void ft_lstadd_back_redir(t_redir_list **lst, t_redir_list *new)
{
    t_redir_list *temp;

    // printf("ft_lstadd_back_redir: lst = %p, new = %p\n", (void *)*lst, (void *)new);

    if (new == NULL)
    {
        // printf("ft_lstadd_back_redir: new is NULL\n");
        return;
    }

    if (*lst == NULL)
    {
        // printf("ft_lstadd_back_redir: list is empty, setting new as head\n");
        *lst = new;
        // printf("ft_lstadd_back_redir: lst after adding new = %p\n", (void *)*lst);
    }
    else
    {
        // printf("ft_lstadd_back_redir: traversing the list\n");
        temp = *lst;
        while (temp->next != NULL)
        {
            // printf("ft_lstadd_back_redir: temp = %p\n", (void *)temp);
            temp = temp->next;
        }
        // printf("ft_lstadd_back_redir: appending new node\n");
        temp->next = new;
        // printf("ft_lstadd_back_redir: lst after appending new = %p\n", (void *)*lst);
    }
}