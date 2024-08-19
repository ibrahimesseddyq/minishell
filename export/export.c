/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:58:19 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/19 10:28:43 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int find_keyx(char *)
{
	int i;

	i = 0;
	while(key[i] && key[i] == env[i])
	{
        if (key[i + 1] == '=' && !env[i + 1])
			return (1); 
		i++;
	}
	return (0);
}

void ft_export(char **str, t_lst *lst)
{
    int exist;
    char **str_split;
    int i;
    i = 1;
    if (!str[1])
    {
        print_export(lst);
    }
    else
    {
        while(str[i])
        {
            exist = get_symbol_exist(str[i], '=');
            if(exist)
            {
                str_split = ft_split(str[i], '=');
                if(!str_split)
                    return ;
                
                // Remove leading and trailing quotes from the value
                char *value = str_split[1];
                while (*value && (*value == '\'' || *value == '\"'))
                {
                    value++;
                }
                int value_len = strlen(value);
                while (value_len > 0 && (value[value_len - 1] == '\'' || value[value_len - 1] == '\"'))
                {
                    value_len--;
                }
                value[value_len] = '\0';
                
                set_env(lst, str_split[0], value, exist);
            }
            else
            {
                set_env(lst, str[i], "", exist);
            }
            i++;
        }
    } 
}