/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:28:09 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/27 13:32:17 by ibes-sed         ###   ########.fr       */
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
	int empty;

	empty = 0;
	i = 1;
	if (!args[1] && !builtins_state(-1, UNSET_BUILTIN, GET_BUILTIN))
		return (ft_exit(0, SET_EXIT_STATUS), 1);

	while (i < nb_args(args))
	{
		if (is_empty(args[i]))
			empty = 1;
		if(check_valid(args[i]))
			set_env(lst, args[i], NULL, '\0');
		i++;
	}
	if (empty)
	{
		ft_exit(1, SET_EXIT_STATUS);
		return (0);
	}
	return (ft_exit(0, SET_EXIT_STATUS), 1);
}
