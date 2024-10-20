/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:55:38 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 16:06:46 by ibes-sed         ###   ########.fr       */
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
	matches = gcalloc((numTexts + 1) * sizeof(char *));
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
	matches[*numMatches] = NULL;
	return (matches);
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

char	**get_files(const char *dir, int *numFiles, t_wildcard_data *data)
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
		if (is_valid_file(ep->d_name, data))
		{
			files = add_file(files, numFiles, ep->d_name);
			if (!files)
				return (closedir(dp), NULL);
		}
		ep = readdir(dp);
	}
	closedir(dp);
	if (files && *numFiles > 1)
		bubble_sort(files, *numFiles);
	return (files);
}

void	wildcard2(const char *pwd, int level,
		t_wildcard_data *data, t_wd_redir_res *res)
{
	char	**files;
	char	**validpaths;
	int		count;
	int		validcount;
	int		i;

	(1) && (validcount = 0, count = 0);
	(1) && (i = 0, files = NULL, validpaths = NULL,
			files = get_files(pwd, &count, data));
	if (!files)
		return (add_to_found(data->found_files
				, data->found_count, data->pattern[level]));
	validpaths = filterstrings(data->pattern[level],
			(char **)files, count, &validcount);
	if (validcount == 0)
		add_to_found(data->found_files,
			data->found_count, data->pattern[level]);
	else
	{
		while (i < validcount)
		{
			mark_file_as_found(data, validpaths, &i);
		}
	}
	res->size = i;
}
