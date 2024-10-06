/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:30:25 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 15:38:16 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_and_open_file(const char *file, int flags, mode_t mode)
{
	struct stat	sb;
	int			fd;

	if (stat(file, &sb) == -1)
	{
		fd = open(file, flags, mode);
		if (fd == -1)
		{
			if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
				write(2, "Permission denied\n", 19);
			else
				write(2, "No such file or directory\n", 27);
			ft_exit(1, SET_EXIT_STATUS);
			return (-2);
		}
		return (fd);
	}
	if (!S_ISREG(sb.st_mode))
		return (write(2, "Error: Path is not a regular file\n", 35)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	fd = open(file, flags, mode);
	if (fd == -1)
		return (write(2, "Error opening file", 19)
			, ft_exit(1, SET_EXIT_STATUS), -2);
	return (fd);
}

int	check_ambiguious_wildcard(char *str)
{
	char	*del;
	int		i;

	i = 0;
	del = get_splitted_char(1);
	while (str[i])
	{
		if (str[i] == *del)
			return (1);
		i++;
	}
	return (0);
}

int	handle_ambiguous(char *str)
{
	if (check_ambiguious_wildcard(str))
	{
		write(2, "ambiguous redir\n", 17);
		ft_exit(1, SET_EXIT_STATUS);
		return (-1);
	}
	return (1);
}
