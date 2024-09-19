/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:16:59 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/19 01:19:40 by ibes-sed         ###   ########.fr       */
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

int	check_just_n(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int		i;
	bool	n_option;

	i = 1;
	n_option = false;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-", 1) == 0)
		{
			if (!check_just_n(args[i] + 1))
				break ;
			n_option = true;
			i++;
		}
		while (args[i])
		{
			write(1, args[i], strlen(args[i]));
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!n_option)
		write(1, "\n", 1);
	return (SUCCESS);
}
