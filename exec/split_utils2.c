/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:19:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/21 05:37:00 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_splitted_char(int index)
{
	static char	c[5];

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

char	*get_null_str(void)
{
	char	*empty_str;

	empty_str = NULL;
	empty_str = gcalloc(2);
	empty_str[0] = *get_splitted_char(5);
	empty_str[1] = '\0';
	return (empty_str);
}