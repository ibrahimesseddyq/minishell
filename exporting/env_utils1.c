/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:44:36 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 21:59:06 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_symbol_exist(char *str, char symbol)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == symbol)
			return (1);
		i++;
	}
	return (0);
}

void	print_export(t_lst *lst)
{
	t_lst	*head;

	head = lst;
	while (head)
	{
		if (head->set)
		{
			if (head->signe != '=')
			{
				printf("declare -x %s\n", head->key);
			}
			else if (head->value)
			{
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
			}
			else
				printf("declare -x %s=\"\"\n", head->key);
		}
		head = head->next;
	}
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

char	*trim_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (NULL);
	if (is_quote(str[0]) && is_quote(str[len - 1]))
	{
		return (ft_substr(str, 1, len - 2));
	}
	return (str);
}

void	apppend_to_var(char **key, char **value,
		char **temp, char *str, t_lst *lst)
{
	*temp = strdup(str);
	*key = strtok(*temp, "+=");
	*value = ft_strchr(str, '=');
	if (*value)
		(*value)++;
	if (*value && **value)
		*value = trim_quotes(*value);
	else
		*value = "";
	append_env(lst, *key, *value);
}
