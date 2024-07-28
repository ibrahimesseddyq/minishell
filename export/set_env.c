/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:11:05 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/28 15:51:12 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"


char *find_key_2(char *env)
{
	int i;
	i = 0;
	char *tmp;
	tmp = NULL;
	printf("----->%c\n", env[0]);
	if (env[0] == '=')
		printf("hiii ====");
	while (env[i] && env[i] != '=')
	{
		printf("ddd\n");
		if (env[i + 1] != '=' )
			printf("hiiiiii %c\n",env[i]);
		i++;
	}
	tmp = ft_strdup(ft_substr(env, 0, i));
	return (tmp);
}

void	set_env(t_lst *lst, char *str_expo)
{
	t_lst	*new;
	t_lst	*tmp;
	char	*key;
	char	*new_value;

	new = NULL;
	tmp = lst;
	key = find_key_2(str_expo);
	if (!key)
		printf("NULL key \n");
	exit(1);
	new_value = ft_strchr(str_expo, '=') + 1;
		
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			lst->value = new_value;
			return ;
		}
		lst = lst->next;
	}
	lst = tmp; 
	new = ft_lstadd_new_env(key, '=', new_value);
	ft_lstadd_back_env(&lst, new);
}
