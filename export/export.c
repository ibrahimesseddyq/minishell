/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:58:19 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/28 10:06:53 by ynachat          ###   ########.fr       */
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

char	*export(char *str_expo, t_lst *lst)
{
	int	i;
	int k;
// char **key, char *the_env
	i = 0;
	k = 0;
	if (!str_expo)
		return (NULL);
	while (str_expo)
	{	
		k =  find_keyx(key[i], the_env);
		if (k == 1)
			return (ft_strchr(key[i], '=') + 1);
		i++;
	}
	return (NULL);
}



