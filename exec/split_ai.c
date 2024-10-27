/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:59:57 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/26 20:45:56 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_splitted_char(char c, int index)
{
	char	*splitted_char;

	splitted_char = NULL;
	splitted_char = get_splitted_char(index);
	*splitted_char = c;
}

int	check_if_exists( char *str, char c)
{
	int	i;

	i = 0;
	if (c == 34 || c == 36 || c == 39)
		return (1);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	get_next_char(char c)
{
	if (c >= 5)
		return (c + 1);
	return (5);
}

void	initialize_which_to_split_with(char *c, int *i,
		int *order_of_char, char *found_char)
{
	*c = get_next_char(33);
	*i = 0;
	*order_of_char = 0;
	*found_char = 0;
}

char	which_to_split_with(char **strs, int index)
{
	char	c;
	int		i;
	int		order_of_char;
	char	found_char;

	initialize_which_to_split_with(&c, &i, &order_of_char, &found_char);
	while (order_of_char < index)
	{
		i = 0;
		while (strs[i])
		{
			if (check_if_exists(strs[i], c) || (c != 0 && c == found_char))
			{
				c = get_next_char(c);
				i = 0;
			}
			else
				i++;
		}
		order_of_char++;
		found_char = c;
	}
	return (set_splitted_char(c, index), c);
}
