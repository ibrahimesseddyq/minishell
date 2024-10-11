/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:30:25 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 15:51:32 by ibes-sed         ###   ########.fr       */
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