/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:55:38 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/14 22:42:28 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	match(char *pattern, const char *text)
{
	if (*pattern == '\0' && *text == '\0')
		return (1);
	if (*pattern == *get_splitted_char(4))
	{
		if (*(pattern + 1) == '\0')
			return (1);
		while (*text)
		{
			if (match(pattern + 1, text))
				return (1);
			text++;
		}
		return (match(pattern + 1, text));
	}
	if (*text != '\0' && (*pattern == *text))
		return (match(pattern + 1, text + 1));
	return (0);
}

char	**filterstrings(char *pattern
		, char *texts[], int numTexts, int *numMatches)
{
	char	**matches;
	int		i;

	*numMatches = 0;
	matches = gcalloc(numTexts * sizeof(char *));
	i = 0;
	if (!matches)
		return (NULL);
	while (i < numTexts)
	{
		if (match(pattern, texts[i]))
		{
			matches[*numMatches]
				= gcalloc((strlen(texts[i]) + 1) * sizeof(char));
			if (!matches[*numMatches])
				return (NULL);
			ft_strcpy(matches[*numMatches], texts[i]);
			(*numMatches)++;
		}
		i++;
	}
	return (matches);
}

static int	is_valid_file(char *filename, char *pwd)
{
	return (ft_strcmp(filename, ".") != 0
		&& ft_strcmp(filename, "..") != 0 && (filename[0] != '.' && pwd[0] !='.'));
}

static char	**add_file(char **files, int *numFiles, char *filename)
{
	files = ft_realloc(files, (*numFiles) * sizeof(char *),
			(*numFiles + 1) * sizeof(char *));
	if (!files)
		return (NULL);
	files[*numFiles] = gcalloc((ft_strlen(filename) + 1) * sizeof(char));
	if (!files[*numFiles])
		return (NULL);
	ft_strcpy(files[*numFiles], filename);
	(*numFiles)++;
	return (files);
}

char	**get_files(const char *dir, int *numFiles)
{
	DIR				*dp;
	struct dirent	*ep;
	char			**files;

	*numFiles = 0;
	files = NULL;
	dp = opendir(dir);
	if (dp == NULL)
		return (write(2, "Couldn't open the directory\n", 28), NULL);
	ep = readdir(dp);
	while (ep)
	{
		if (is_valid_file(ep->d_name, dir))
		{
			files = add_file(files, numFiles, ep->d_name);
			if (!files)
				return (closedir(dp), NULL);
		}
		ep = readdir(dp);
	}
	return (closedir(dp), files);
}
