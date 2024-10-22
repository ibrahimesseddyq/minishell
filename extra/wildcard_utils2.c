/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:05 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 00:09:15 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	*replace_by_wd(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (*get_splitted_char(4) == file[i])
			file[i] = '*';
		i++;
	}
	return (file);
}

void	add_to_found_2(char ***found_files, int *found_count, const char *file)
{
	*found_files = ft_realloc(*found_files, (*found_count) * sizeof(char *),
			(*found_count + 1) * sizeof(char *));
	if (!(*found_files))
		return ;
	(*found_files)[*found_count] = gcalloc((strlen(file) + 1) * sizeof(char));
	if (!(*found_files)[*found_count])
		return ;
	file = replace_by_wd((char *)file);
	ft_strcpy((*found_files)[*found_count], (char *)file);
	(*found_count)++;
}
