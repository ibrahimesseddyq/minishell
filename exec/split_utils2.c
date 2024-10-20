/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:19:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 15:19:03 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_splitted_char(int index)
{
	static char	c[4];

	if (c[index - 1] == 0)
		c[index - 1] = 33;
	return (&c[index - 1]);
}

char	*skip_char(const char *input, char skip)
{
	size_t	len;
	char	*result;
	size_t	j;
	size_t	i;

	if (input == NULL)
		return (NULL);
	i = 0;
	len = strlen(input);
	result = (char *)gcalloc(len + 1);
	if (result == NULL)
		return (NULL);
	j = 0;
	while (i < len)
	{
		if (input[i] != skip)
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
