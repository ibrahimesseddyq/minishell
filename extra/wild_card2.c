/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:55:38 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/15 22:40:08 by ibes-sed         ###   ########.fr       */
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
		printf("pattern [%s] text [%s]\n", pattern, texts[i]);
		if (match(pattern, texts[i]))
		{
			printf("  matched\n");
			matches[*numMatches]
				= gcalloc((strlen(texts[i]) + 1) * sizeof(char));
			if (!matches[*numMatches])
				return (NULL);
			ft_strcpy(matches[*numMatches], texts[i]);
			(*numMatches)++;
		}
		i++;
	}
	for (int i = 0; matches[i]; i++)
	{
		printf("matches[i] : [%s]\n", matches[i]);
	}
	return (matches);
}

static int	is_valid_file(char *filename, t_wildcard_data *data)
{
	// printf("pwd is [%s] and fn is [%s]\n",data->pattern[0], filename);
	if(data->pattern[0][0] != '.')
	{
		if(filename[0] == '.')
			return (0);
		return (1);
	}
	else
	{
		if(filename[0] == '.')
			return (1);
		return (0);
	}
}

static char **add_file(char **files, int *numFiles, char *filename)
{
    // Allocate space for the new file plus a NULL terminator
    files = ft_realloc(files, (*numFiles + 1) * sizeof(char *),
                       (*numFiles + 2) * sizeof(char *));
    if (!files)
        return NULL;

    files[*numFiles] = gcalloc((ft_strlen(filename) + 1) * sizeof(char));
    if (!files[*numFiles])
    {
        return NULL;
    }

    ft_strcpy(files[*numFiles], filename);
    (*numFiles)++;
    files[*numFiles] = NULL;  // Set the last element to NULL
    return files;
}

char	**get_files(const char *dir, int *numFiles, t_wildcard_data *data)
{
	DIR				*dp;
	struct dirent	*ep;
	char			**files;

	*numFiles = 0;
	printf("dir [%s]\nnum Files [%d]\npattern [%s]\n", dir, *numFiles, data->pattern[0]);
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
	return (closedir(dp), files);
}

void	wildcard2(const char *pwd, int level, t_wildcard_data *data, t_wd_redir_res *res)
{
	char	**files;
	char	**validpaths;
	int		count;
	int		validcount;
	int		i;

	// printf("pwd 2 is [%s]\n", pwd);
	(1) && (validcount = 0, count = 0);
	(1) && (i = 0, files = NULL, validpaths = NULL,
			files = get_files(pwd, &count, data));
		for (int i = 0; files[i]; i++)
	{
		printf("files[i] : [%s]\n", files[i]);
	}
	if (!files)
		return (add_to_found(data->found_files
				, data->found_count, data->pattern[level]));
	validpaths = filterstrings(data->pattern[level],
			(char **)files, count, &validcount);
	for (int i = 0; validpaths[i]; i++)
	{
		printf("valid path[i] : [%s]\n", validpaths[i]);
	}
		printf("i is [%d] valid count is [%d]\n", i, validcount);
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
	res->size = i;
}