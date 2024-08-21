#include "../minishell.h"

void ft_env(t_lst *env_list)
{
    t_lst *current = env_list;
    while (current != NULL)
    {
        if (current->key != NULL && current->value != NULL)
        {
            if (current->signe == '=')
            {
                if (current->value)
                    printf("%s%c%s\n",current->key ,current->signe ,current->value);
                else
                    printf("%s%c\n",current->key ,current->signe);
            }
        }
        current = current->next;
    }
}