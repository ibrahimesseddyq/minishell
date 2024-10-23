/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:13:20 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 03:58:45 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_delimiter_occurrences(char *s, char delimiter)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == delimiter)
			count++;
		s++;
	}
	return (count);
}

static char	**split_string(char *s, char delimiter)
{
	return (ft_split(s, delimiter));
}

char	**alloc_for_split_all_strings(char **array, char delimiter)
{
	int		total_count;
	int		i;
	char	**result;

	total_count = 0;
	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
		total_count += count_delimiter_occurrences(array[i++], delimiter) + 1;
	result = gcalloc((total_count + 1) * sizeof(char *));
	return (result);
}

char	**split_all_strings(char **array, char delimiter)
{
	int		i;
	char	**result;
	int		result_index;
	int		k;
	char	**split_result;

	result_index = 0;
	result = alloc_for_split_all_strings(array, delimiter);
	i = 0;
	k = 0;
	while (array[i])
	{
		split_result = split_string(array[i], delimiter);
		if (!split_result)
			return (NULL);
		k = 0;
		while (split_result[k])
		{
			result[result_index++] = split_result[k];
			k++;
		}
		i++;
	}
	result[result_index] = NULL;
	return (result);
}
