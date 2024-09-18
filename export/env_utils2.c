/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 21:59:01 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_existing_var(char *str, char **key,
		char **value, char **temp, t_lst *lst)
{
	*temp = strdup(str);
	*key = strtok(*temp, "=");
	*value = ft_strchr(str, '=');
	if (*value)
		(*value)++;
	if (*value && **value)
		*value = trim_quotes(*value);
	else
		*value = "";
	set_env(lst, *key, *value, 1);
}

void	export_var(char **str, t_lst *lst, int i)
{
	int		exist;
	int		append_mode;
	char	*key;
	char	*value;
	char	*temp;

	append_mode = get_symbol_exist(str[i], '+')
		&& get_symbol_exist(str[i], '=');
	if (append_mode)
		apppend_to_var(&key, &value, &temp, str[i], lst);
	else
	{
		exist = get_symbol_exist(str[i], '=');
		if (exist)
			handle_existing_var(str[i], &key, &value, &temp, lst);
		else
			set_env(lst, str[i], "", exist);
	}
}

void	append_env(t_lst *lst, char *key, char *new_value)
{
	t_lst	*tmp;
	char	*existing_value;
	char	*combined_value;

	tmp = lst;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			if (lst->value)
				existing_value = lst->value;
			else
				existing_value = "";
			combined_value = malloc(ft_strlen(existing_value)
					+ ft_strlen(new_value) + 1);
			strcpy(combined_value, existing_value);
			strcat(combined_value, new_value);
			lst->value = combined_value;
			return ;
		}
		lst = lst->next;
	}
	lst = tmp;
	ft_lstadd_back_env(&lst, ft_lstadd_new_env(key, new_value, '='));
}

t_lst	*choose_add_set_env(char *key, char *new_value, int sign)
{
	if (sign)
		return (ft_lstadd_new_env(key, new_value, '='));
	else
		return (ft_lstadd_new_env(key, new_value, '\0'));
}
