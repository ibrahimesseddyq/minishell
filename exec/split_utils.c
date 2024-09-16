/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:13:20 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/16 17:45:00 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../minishell.h"
#include "../frontend/frontend.h"

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

char	**alloc_for_split_string(char *s, char delimiter)
{
	int		count;
	char	**result;

	count = count_delimiter_occurrences(s, delimiter) + 1;
	result = malloc((count + 1) * sizeof(char *));
	return (result);
}

static char	**split_string(char *s, char delimiter)
{
	char	**result;
	int		index;
	char	*start;
	char	*end;

	index = 0;
	result = alloc_for_split_string(s, delimiter);
	if (!result)
		return (NULL);
	start = s;
	end = strchr(start, delimiter);
	while (end)
	{
		result[index] = strndup(start, end - start);
		if (!result[index])
			return (NULL);
		index++;
		start = end + 1;
		end = strchr(start, delimiter);
	}
	result[index] = strdup(start);
	if (!result[index])
		return (NULL);
	return (result[++index] = NULL, result);
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
	result = malloc((total_count + 1) * sizeof(char *));
	return (result);
}

char	**split_all_strings(char **array, char delimiter)
{
	int		i;
	char	**result;
	int		result_index;
	int		k;
	char	**split_result;

	if (!result)
		return (NULL);
	result_index = 0;
	result = alloc_for_split_all_strings(array, delimiter);
	i = 0;
	k = 0;
	while (array[i])
	{
		printf("[split_all_strings] array[i] is [%s]\n", array[i]);
		split_result = split_string(array[i], delimiter);
		if (!split_result)
			return (NULL);
		while (split_result[k])
			result[result_index++] = split_result[k++];
		i++;
	}
	result[result_index] = NULL;
	for (int i = 0;result[i]; i++)
	{
		printf("[split_all_strings] result [%s]\n", result[i]);
	}
	return (result);
}
