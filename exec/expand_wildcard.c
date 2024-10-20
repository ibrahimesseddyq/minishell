/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:42:32 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 17:46:03 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_pattern(char *str, char *pattern)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (1);
			while (*str && *str != *pattern)
				str++;
		}
		if (*str != *pattern)
			return (0);
		str++;
		pattern++;
	}
	return (*str == '\0');
}

char	**get_matching_files(char *pattern, int *file_count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	*file_count = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = gcalloc(sizeof(char *) * 100);
	if (!(files))
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (!entry)
	{
		entry = readdir(dir);
		if (match_pattern(entry->d_name, pattern))
			files[i++] = ft_strdup(entry->d_name);
	}
	files[i] = NULL;
	*file_count = i;
	closedir(dir);
	return (files);
}
