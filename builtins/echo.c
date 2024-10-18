/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:16:59 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/18 19:17:25 by ynachat          ###   ########.fr       */
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

	(1) && (i = 1, n_option = false);
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
		{
			if (!check_just_n(args[i] + 1))
				break ;
			n_option = true;
			i++;
		}
		while (args[i])
		{
			if (args[i][0])
			{
				write(1, args[i], strlen(args[i]));
				if (args[i + 1])
					write(1, " ", 1);
			}
			i++;
		}
	}
	if (!n_option)
		write(1, "\n", 1);
	return (ft_exit(0, SET_EXIT_STATUS), SUCCESS);
}
