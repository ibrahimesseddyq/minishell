#include "../minishell.h"

void ft_env(t_lst *env_list)
{
    t_lst *current = env_list;
    while (current != NULL)
    {
        if (current->key != NULL && current->value != NULL)
        {
            printf("%s=%s\n", current->key, current->value);
        }
        current = current->next;
    }
}