/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 10:26:50 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_setting_var(char *str, t_export_var *state, t_lst **lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("key is [%s]\n", tmp->key);
		tmp = tmp->next;
	}
	state->temp = ft_strdup(str);
	state->key = ft_strtok(state->temp, "=");
	state->value = ft_strchr(str, '=');
	if (get_env_isset(lst, state->key) && !state->exist)
		return ;
	if (state->value)
		state->value++;
	else
		state->value = "";
	if (!state->exist)
		set_env(lst, state->key, "", state->exist);
	else
		set_env(lst, state->key, state->value, state->exist);
}

void	export_var(char **str, t_lst **lst, int i)
{
	t_export_var	state;

	state.append_mode = get_symbol_exist(str[i], '+')
		&& get_symbol_exist(str[i], '=');
	if (lst && !*lst)
	{
		printf("lst is null\n");
		(*lst) = gcalloc(sizeof(t_lst));
		(*lst)->key = ft_strdup("hhhhh");
		(*lst)->value = ft_strdup("");	
		(*lst)->set = 0;
		(*lst)->signe = 0;
		(*lst)->next = NULL;
	}
	if (state.append_mode
		&& get_symbol_exist(str[i], '+') > get_symbol_exist(str[i], '='))
		state.append_mode = 0;
	if (state.append_mode)
		apppend_to_var(&state, str[i], lst);
	else
	{
		state.exist = get_symbol_exist(str[i], '=');
		handle_setting_var(str[i], &state, lst);
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
