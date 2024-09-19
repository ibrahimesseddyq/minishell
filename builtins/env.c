/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:19:51 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/19 01:21:55 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	t_env(t_lst *env_list)
{
	t_lst	*current;

	current = env_list;
	while (current != NULL)
	{
		if (current->key != NULL && current->value != NULL && current->set)
		{
			if (current->signe == '=')
			{
				if (current->value)
					printf ("%s%c%s\n", current->key,
						current->signe, current->value);
				else
					printf ("%s%c\n", current->key, current->signe);
			}
		}
		current = current->next;
	}
}
