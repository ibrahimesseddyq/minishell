/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:33:59 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 20:10:07 by ynachat          ###   ########.fr       */
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
