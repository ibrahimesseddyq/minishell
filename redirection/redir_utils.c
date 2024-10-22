/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:48:07 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 17:48:29 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_just(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

char	*make_filename(char *file)
{
	file = skip_char(file, *get_splitted_char(5));
	if (!file[0])
		return (NULL);
	if (contains_just(file, *get_splitted_char(3)) || !file[0])
	{
		return (ft_strdup(""));
	}
	file = skip_char(file, *get_splitted_char(3));
	return (file);
}
