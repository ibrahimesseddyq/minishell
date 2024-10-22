/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:44:36 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 00:06:41 by ibes-sed         ###   ########.fr       */
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
			return (i);
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

void	apppend_to_var(t_export_var *state, char *str, t_lst *lst)
{
	state->temp = ft_strdup(str);
	state->key = ft_strtok(state->temp, "+=");
	state->value = ft_strchr(str, '=');
	if (state->value)
		(state->value)++;
	if (state->value && *(state->value))
		state->value = trim_quotes(state->value);
	else
		state->value = "";
	append_env(lst, state->key, state->value);
}
