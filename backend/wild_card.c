/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:47:30 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/20 00:39:58 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

bool	match(const char *pattern, const char *text)
{
	if (*pattern == '\0' && *text == '\0')
		return (true);
	if (*pattern == '*')
		return (match(pattern + 1, text)
			|| (*text != '\0' && match(pattern, text + 1)));
	if (*text != '\0' && (*pattern == *text))
		return (match(pattern + 1, text + 1));
	return (false);
}

char	**filterstrings(const char *pattern
		, const char *texts[], int numTexts, int *numMatches)
{
	char	**matches;
	int		i;

	*numMatches = 0;
	matches = malloc(numTexts * sizeof(char *));
	i = 0;
	if (!matches)
		return (NULL);
	while (i < numTexts)
	{
		if (match(pattern, texts[i]))
		{
			matches[*numMatches]
				= malloc((strlen(texts[i]) + 1) * sizeof(char));
			if (!matches[*numMatches])
				return (NULL);
			strcpy(matches[*numMatches], texts[i]);
			(*numMatches)++;
		}
		i++;
	}
	return (matches);
}

void	add_to_found(char ***found_files, int *found_count, const char *file)
{
	*found_files = realloc(*found_files, (*found_count + 1) * sizeof(char *));
	if (!(*found_files))
		return ;
	(*found_files)[*found_count] = malloc((strlen(file) + 1) * sizeof(char));
	if (!(*found_files)[*found_count])
		return ;
	strcpy((*found_files)[*found_count], file);
	(*found_count)++;
}

char	**get_files(const char *dir, int *numFiles)
{
	DIR				*dp;
	struct dirent	*ep;
	char			**files;

	*numFiles = 0;
	files = NULL;
	dp = opendir(dir);
	if (dp != NULL)
	{
		ep = readdir(dp);
		while (ep)
		{
			if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
			{
				files = realloc(files, (*numFiles + 1) * sizeof(char *));
				if (!files)
					return (NULL);
				files[*numFiles]
					= malloc((strlen(ep->d_name) + 1) * sizeof(char));
				if (!files[*numFiles])
					return (NULL);
				strcpy(files[*numFiles], ep->d_name);
				(*numFiles)++;
			}
			ep = readdir(dp);
		}
		closedir(dp);
	}
	else
		write(2, "Couldn't open the directory\n", 28);
	return (files);
}

void	wildcard(const char *pwd, int level, t_wildcard_data *data)
{
	char	**files;
	char	**validpaths;
	int		count;
	int		validcount;
	int		i;

	i = 0;
	files = NULL;
	validpaths = NULL;
	files = get_files(pwd, &count);
	if (!files)
		return (add_to_found(data->found_files
				, data->found_count, data->pattern[level]));
	validcount = 0;
	count = 0;
	validpaths = filterstrings(data->pattern[level],
			(const char **)files, count, &validcount);
	if (validcount == 0)
		add_to_found(data->found_files,
			data->found_count, data->pattern[level]);
	else
	{
		while (i < validcount)
		{
			add_to_found(data->found_files, data->found_count, validpaths[i]);
			i++;
		}
	}
}

int	main()
{
	char *pattern[] = {"*t", "*.c"};
	int levels = sizeof(pattern) / sizeof(pattern[0]);
	char **found_files = NULL;
	int found_count = 0;

	t_wildcard_data data = {pattern, levels, &found_files, &found_count};

	char current_dir[1024];
	if (!getcwd(current_dir, sizeof(current_dir)))
	{
		printf("Error getting current directory\n");
		return 1;
	}
	wildcard(current_dir, 0, &data);
	for (int i = 0; i < found_count; i++)
	{
		printf("%s\n", found_files[i]);
	}
	return 0;
}
