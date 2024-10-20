/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:41:44 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 16:15:23 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(char **arr, int n)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	j = 0;
	while (i < n - 1)
	{
		swapped = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				swap_strings(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
			j++;
		}
		j = 0;
		if (swapped == 0)
			break ;
		i++;
	}
}

int	is_valid_file(char *filename, t_wildcard_data *data)
{
	if (data->pattern[0][0] != '.')
	{
		if (filename[0] == '.')
			return (0);
		return (1);
	}
	else
	{
		if (filename[0] == '.')
			return (1);
		return (0);
	}
}

void	mark_file_as_found(t_wildcard_data *data, char	**validpaths, int *i)
{
	add_to_found(data->found_files, data->found_count, validpaths[*i]);
	(*i)++;
}

char	*alloc_del(void)
{
	char			*del;

	del = gcalloc(2);
	del[0] = *get_splitted_char(1);
	del[1] = '\0';
	return (del);
}
