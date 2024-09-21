/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:22:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/21 04:46:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_error_exist(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	my_exit(char **argv, int argc)
{
	long	exit_value;
	int		error_exist;

	error_exist = 0;
	if (!argv[1])
		ft_exit(0, EXIT_PROGRAM);
	if (argc > 2)
		return (write(2, "minishell: exit: too many arguments\n"
				, 37), ft_exit(EXIT_FAILURE, SET_EXIT_STATUS), 0);
	else
	{
		error_exist = check_error_exist(argv[1]);
		exit_value = atoi(argv[1]);
		if (exit_value > INT_MAX || exit_value < INT_MIN || error_exist)
		{
			write(2, "numeric argument required\n", 27);
			ft_exit(255, EXIT_PROGRAM);
		}
		else
			ft_exit(exit_value % 256, EXIT_PROGRAM);
	}
	ft_exit(0, SET_EXIT_STATUS);
	return (1);
}
