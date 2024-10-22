/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:33:59 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 17:34:40 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst	*choose_add_set_env(char *key, char *new_value, int sign)
{
	if (sign)
		return (ft_lstadd_new_env(key, new_value, '='));
	else
		return (ft_lstadd_new_env(key, new_value, '\0'));
}

t_lst	*choose_add_set_env2(char *key,
		char *new_value, int sign, t_export_var *state)
{
	if (sign)
		return (ft_lstadd_new_env2(key, new_value, '=', state));
	else
		return (ft_lstadd_new_env2(key, new_value, '\0', state));
}
