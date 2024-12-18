/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:22:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/27 21:27:00 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	len = end - start + 1;
	result = (char *)gcalloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strncpy(result, start, len);
	result[len] = '\0';
	return (result);
}

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
	str = trim_spaces(str);
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
	__int128	exit_value;
	int			error_exist;

	error_exist = 0;
	if (!argv[1])
		return (write(1, "exit\n", 6),
			gc_free_all(), ft_exit(0, EXIT_PROGRAM), 0);
	error_exist = check_error_exist(argv[1]);
	exit_value = ft_atoi128(argv[1]);
	if (exit_value > LLONG_MAX || exit_value < LLONG_MIN
		|| error_exist || !argv[1][0] || (argv[1][0] && argv[1][1]
		&& (argv[1][0] == '-' || argv[1][0] == '+') && !ft_isnum(argv[1][1])))
		return (write(1, "exit\n", 6),
			write(2, "numeric argument required\n", 27),
			gc_free_all(), ft_exit(255, EXIT_PROGRAM));
	else if (!error_exist && argc < 3)
	{
		gc_free_all();
		write(1, "exit\n", 6);
		ft_exit(exit_value % 256, EXIT_PROGRAM);
	}
	if (argc > 2)
		return (write(2, "minishell: exit: too many arguments\n"
				, 37), ft_exit(EXIT_FAILURE, SET_EXIT_STATUS), 1);
	return (ft_exit(0, SET_EXIT_STATUS), write(1, "exit\n", 6), 1);
}
