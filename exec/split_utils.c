/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:13:20 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/02 08:23:59 by ibes-sed         ###   ########.fr       */
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

char	**alloc_for_split_string(char *s, char delimiter)
{
	int		count;
	char	**result;

	count = count_delimiter_occurrences(s, delimiter) + 1;
	result = gcalloc((count + 1) * sizeof(char *));
	return (result);
}

static char	**split_string(char *s, char delimiter)
{
	char	**result;
	int		index;
	char	*start;
	char	*end;
	char	*current;

	(1) && (index = 0, result = NULL);
	// printf("[split_string] string s %s, del %d\n", s, delimiter);
	result = alloc_for_split_string(s, delimiter);
	if (!result)
		return (NULL);
	start = s;
	end = strchr(start, delimiter);
	printf("\n\nstart [%s]  end is [%s]\n\n", start, end);
	while (end)
	{
		current = strndup(start, end - start);
			printf("\n\ncurrent [%s]\n\n", current);

		// if (!current[0] && index == 0)
		// 	return (ft_exit(127, SET_EXIT_STATUS),
		// 		write(2, "command not found 6\n", 19), NULL);
		if (current[0] != '\0')
		{
			result[index] = current;
			if (!result[index])
				return (NULL);
			printf("result whle splitting [%s]\n", result[index]);
			if (result[index][0] == '\0')
				printf("empty\n");
			index++;
		}
		start = end + 1;
		end = strchr(start, delimiter);
	}
	result[index] = strdup(start);
	if (!result[index])
		return (NULL);
	result[++index] = NULL;
	printf("result\n\n");
	for(int i = 0; result[i]; i++)
	{
		printf("result[i] [%s]\n", result)
	}
	return (result);
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
		// printf("[split_all_strings] before array [i] %s , del %c\n", array[i], delimiter);
		split_result = split_string(array[i], delimiter);
		// printf("[split_all_strings] after array [i] %s , del %c, split res [%s]\n", array[i], delimiter, split_result);
		if (!split_result)
			return (NULL);
		k = 0;
		while (split_result[k])
		{
			result[result_index++] = split_result[k];
			// printf("result[index] [%s]\n", result[result_index - 1]);
			k++;
		}
		i++;
	}
	result[result_index] = NULL;
	// for(int i = 0; result[i]; i++)
	// 	printf("[split_all_strings] result [%s]\n", result[i]);
	return (result);
}
