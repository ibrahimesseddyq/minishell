/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:47:30 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/28 03:09:13 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	match(char *pattern, const char *text)
{
	// If both pattern and text are fully consumed, it's a match

	if (*pattern == '\0' && *text == '\0')
		return (1);

	// If the pattern contains '*', it can match zero or more characters
	if (*pattern == '*')
	{
		// If '*' is the last character, it matches the rest of the string
		if (*(pattern + 1) == '\0')
			return (1);
		
		// Try to match '*' with zero characters or skip one character in text
		while (*text)
		{
			if (match(pattern + 1, text))
				return (1);
			text++;
		}
		// Also try matching with zero characters
		return (match(pattern + 1, text));
	}

	// If characters match, move to the next character in both pattern and text
	if (*text != '\0' && (*pattern == *text))
		return (match(pattern + 1, text + 1));

	// No match
	return (0);
}



char	**filterstrings(char *pattern
		, char *texts[], int numTexts, int *numMatches)
{
	char	**matches;
	int		i;

	*numMatches = 0;
	matches = malloc(numTexts * sizeof(char *));
	i = 0;
	if (!matches)
		return (NULL);
	// printf("pattern [%s], nummatches [%d]\n", pattern, *numMatches);
	// for (int i =0; texts[i]; i++)
	// {
	// 	printf("texts [%s]\n", texts[i]);
	// }
	// printf("numTexts [%d]\n", numTexts);

	while (i < numTexts)
	{
		if (match(pattern, texts[i]))
		{
			// printf("matched text [%s] pattern [%s]\n", texts[i], pattern);
			matches[*numMatches]
				= gcalloc((strlen(texts[i]) + 1) * sizeof(char));
			if (!matches[*numMatches])
				return (NULL);
			ft_strcpy(matches[*numMatches], texts[i]);
			(*numMatches)++;
		}
		i++;
	}
	// for (int i =0; matches[i]; i++)
	// {
	// 	printf("matches [%s]\n", matches[i]);
	// }
	return (matches);
}

void	add_to_found(char ***found_files, int *found_count, const char *file)
{
	*found_files = ft_realloc(*found_files, (*found_count) * sizeof(char *), (*found_count + 1) * sizeof(char *));
	if (!(*found_files))
		return ;
	(*found_files)[*found_count] = gcalloc((strlen(file) + 1) * sizeof(char));
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

	(1) && (*numFiles = 0, files = NULL, dp = opendir(dir));
	if (dp == NULL)
		return (write(2, "Couldn't open the directory\n", 28), NULL);
	ep = readdir(dp);
	while (ep)
	{
		if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
		{
			files = ft_realloc(files, (*numFiles) * sizeof(char *), (*numFiles + 1) * sizeof(char *));
			if (!files)
				return (NULL);
			files[*numFiles]
				= gcalloc((strlen(ep->d_name) + 1) * sizeof(char));
			if (!files[*numFiles])
				return (NULL);
				// printf("[get files] name:[%s]\n", ep->d_name);
			ft_strcpy(files[*numFiles], ep->d_name);
			(*numFiles)++;
		}
		ep = readdir(dp);
	}
	// for(int i =0 ; files[i]; i++)
	// {
	// 	printf("file [%s]\n", files[i]);
	// }
	// printf("numFiles [%d]\n", *numFiles);
	return (closedir(dp), files);
}

void	wildcard(const char *pwd, int level, t_wildcard_data *data)
{
	char	**files;
	char	**validpaths;
	int		count;
	int		validcount;
	int		i;

	(1) && (validcount = 0, count = 0);
	(1) && (i = 0, files = NULL, validpaths = NULL,
			files = get_files(pwd, &count));
	if (!files)
		return (add_to_found(data->found_files
				, data->found_count, data->pattern[level]));
	validpaths = filterstrings(data->pattern[level],
			(char **)files, count, &validcount);
		// printf("count [%d]\n", count);

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


char	*expand_wildcard(char *pwd, int level, t_wildcard_data *data)
{
	int		i;
	char	*expanded_result;
	char	*del;

	del = gcalloc(2);
	wildcard(pwd, level, data);
	del[0] = *get_splitted_char(1); 
	del[1] = '\0';
	if (*(data->found_count) == 0)
		return strdup(data->pattern[level]);

	i = 0;
	expanded_result = gcalloc(1);
	while (i < *(data->found_count))
	{
		expanded_result = ft_realloc(expanded_result, strlen(expanded_result), strlen(expanded_result) + strlen((*data->found_files)[i]) + 2); 
		ft_strcat(expanded_result, (*data->found_files)[i]);
		// printf("found files:[%s]\n", (*data->found_files)[i]);
		if (i < *(data->found_count) - 1)
			ft_strcat(expanded_result, del); 
		i++;
	}
	// printf("expanded_result [%s]\n", expanded_result);
	return expanded_result;
}


// int	main(void)
// {
// 	// Setup test data
// 	char *pattern[] = {"*", "*.c", NULL}; // Searching all files in first level, then all .c files in second level
// 	char **found_files = NULL;
// 	int found_count = 0;
// 	t_wildcard_data data;
// 	char *pwd = "."; // Current directory
// 	char *result;

// 	// Initialize t_wildcard_data struct
// 	data.pattern = pattern;
// 	data.found_files = &found_files;
// 	data.found_count = &found_count;

// 	// Test expand_wildcard function
// 	result = expand_wildcard(pwd, 0, &data); // Start with level 0 of wildcard pattern

// 	if (result)
// 	{
// 		printf("Expanded wildcard result: %s\n", result);
// 		free(result); // Free the allocated result string
// 	}
// 	else
// 	{
// 		printf("No match found.\n");
// 	}

// 	// Free found_files if allocated
// 	for (int i = 0; i < found_count; i++)
// 		free(found_files[i]);
// 	free(found_files);

// 	return 0;
// }