/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/14 01:18:38 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int get_symbol_exist(char *str, char symbol)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == symbol)
			return (1);
		i++;
	}
	return (0);
}
void print_export(t_lst *lst)
{
	t_lst *head;

	head = lst;
	while(head)
	{
        if(head->set)
        {
            if (head->signe != '=')
            {
                printf("declare -x %s\n",head->key);

            }
            else if(head->value)
            {
                printf("declare -x %s=\"%s\"\n",head->key, head->value);
            }
            else
                printf("declare -x %s=\"\"\n",head->key);
        }
		head = head->next;
	}
}
int is_quote(char c)
{
	if(c == '\'' || c == '"')
		return (1);
	return (0);
}
char *trim_quotes(char *str)
{
	int len;

	len = ft_strlen(str);
	if(!str)
		return (NULL);
	if(is_quote(str[0]) && is_quote(str[len - 1]))
	{
		return (ft_substr(str, 1, len - 2));
	}
	return (str);
}
void ft_export(char **str, t_lst *lst)
{
    int exist;
    int append_mode;
    char *key;
    char *value;
    int i;
    char *temp;

    i = 1;
    if (!str[1])
    {
        print_export(lst);
    }
    else
    {
        while (str[i])
        {

            append_mode = get_symbol_exist(str[i], '+') && get_symbol_exist(str[i], '=');
            if (append_mode)
            {
                temp = strdup(str[i]);

                key = strtok(temp, "+=");

                value = ft_strchr(str[i], '=');
                if (value)
                    value++;

                if (value && *value)
                    value = trim_quotes(value);
                else
                    value = "";

                append_env(lst, key, value);
            }
            else
            {
                exist = get_symbol_exist(str[i], '=');
                if (exist)
                {
                    temp = strdup(str[i]);

                    key = strtok(temp, "=");

                    value = ft_strchr(str[i], '=');
                    if (value)
                        value++;

                    if (value && *value)
                        value = trim_quotes(value);
                    else
                        value = "";
                    set_env(lst, key, value, exist);
                }
                else
                {
                    set_env(lst, str[i], "", exist);
                }
            }
            i++;
        }
    }
    if (ft_exit(1, GET_EXIT_STATUS) == 257)
        ft_exit(1, SET_EXIT_STATUS);
}

void append_env(t_lst *lst, char *key, char *new_value)
{
    t_lst *tmp;
    char *existing_value;
    char *combined_value;

    tmp = lst;
    while (lst)
    {
        if (ft_strcmp(lst->key, key) == 0)
        {
            existing_value = lst->value ? lst->value : "";

            combined_value = malloc(ft_strlen(existing_value) + ft_strlen(new_value) + 1);
            if (!combined_value)
                return; 
            strcpy(combined_value, existing_value);
            strcat(combined_value, new_value);

            lst->value = combined_value;

            return;
        }
        lst = lst->next;
    }

    lst = tmp;
    ft_lstadd_back_env(&lst, ft_lstadd_new_env(key, new_value, '='));
}


void	set_env(t_lst *lst, char *key, char *new_value, int sign)
{
	t_lst *new;
	t_lst *tmp;

	new = NULL;
	tmp = lst;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			if (new_value)
            {
				lst->value = ft_strdup(new_value);
                if (sign)
                    lst->signe = '=';
                lst->set = 1;

            }
			else
            {
                lst->set = 0;
                lst->value = ft_strdup("");
                lst->key = ft_strdup("");
            }


			return ;
		}
		lst = lst->next;
	}
	lst = tmp;
	if (sign)
		new = ft_lstadd_new_env(key, new_value, '=');
	else
		new = ft_lstadd_new_env(key, new_value, '\0');
	ft_lstadd_back_env(&lst, new);
}
