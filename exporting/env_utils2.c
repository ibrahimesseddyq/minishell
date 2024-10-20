/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 16:41:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_existing_var(char *str, t_export_var *state, t_lst *lst)
{
	state->temp = ft_strdup(str);
	state->key = ft_strtok(state->temp, "=");
	state->value = ft_strchr(str, '=');
	if (state->value)
		state->value++;
	else
		state->value = "";
	set_env(lst, state->key, state->value, state->exist);
}

void	export_var(char **str, t_lst *lst, int i)
{
	t_export_var	state;

	state.append_mode = get_symbol_exist(str[i], '+')
		&& get_symbol_exist(str[i], '=');
	if (state.append_mode
		&& get_symbol_exist(str[i], '+') > get_symbol_exist(str[i], '='))
		state.append_mode = 0;
	if (state.append_mode)
		apppend_to_var(&state, str[i], lst);
	else
	{
		state.exist = get_symbol_exist(str[i], '=');
		if (state.exist)
			handle_existing_var(str[i], &state, lst);
		else
			set_env(lst, str[i], "", state.exist);
	}
}

static void	set_var(t_lst	*lst, char	*combined_value)
{
	lst->set = 1;
	lst->signe = '=';
	lst->value = combined_value;
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
				existing_value = ft_strdup("");
			combined_value = gcalloc(ft_strlen(existing_value)
					+ ft_strlen(new_value) + 1);
			ft_strcpy(combined_value, existing_value);
			ft_strcat(combined_value, new_value);
			set_var(lst, combined_value);
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
