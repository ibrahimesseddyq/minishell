/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:28:09 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/21 05:36:15 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	alpha_num(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] >= '0' && str[0] <= '9' && i == 0)
			return (0);
		if (!alpha_num(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_empty(char *str)
{
	if (!str[0])
		return (1);
	return (0);
}

int	unset(char **args, t_lst *lst)
{
	int	i;
	int	error;

	(1) && (i = 1, error = 0);
	while (i < nb_args(args))
	{
		if (!check_valid1(args[i]) || !args[i][0])
		{
			write(2, "invalid identifier\n", 20);
			error = 1;
		}
		else
		{
			if (!get_env(lst, args[i]))
			{
				i++;
				continue ;
			}
			set_env(lst, args[i], NULL, '\0');
		}
		i++;
	}
	if (error)
		return (ft_exit(1, SET_EXIT_STATUS), 0);
	return (ft_exit(0, SET_EXIT_STATUS), 1);
}
