/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:30:25 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 01:32:31 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_error_redir_out(t_redir *redir)
{
	if (redir->file && !redir->file[0])
		return (write(2, "No such file or dir\n", 21), -2);
	if (!redir->file)
		return (write(2, "ambigiuos redir\n", 17), -2);
	if (!check_dir_exist(redir->file))
		return (-2);
	return (1);
}
