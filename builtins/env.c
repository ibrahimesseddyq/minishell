#include "../minishell.h"

void ft_env(t_lst *env_list)
{
    t_lst *current = env_list;
    
    printf("ssd\n");
    while (current != NULL)
    {
        // TO FIX : doesnt print =
        // if (current->signe == '=')
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}