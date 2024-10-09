/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:47:30 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/09 22:37:29 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

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
		if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0 && ep->d_name[0] != '.')
		{
			files = ft_realloc
				(files, (*numFiles) * sizeof(char *), (*numFiles + 1) * sizeof(char *));
			if (!files)
				return (NULL);
			files[*numFiles]
				= gcalloc((strlen(ep->d_name) + 1) * sizeof(char));
			if (!files[*numFiles])
				return (NULL);
			ft_strcpy(files[*numFiles], ep->d_name);
			(*numFiles)++;
		}
		ep = readdir(dp);
	}
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
		return (ft_strdup(data->pattern[level]));
	i = 0;
	expanded_result = gcalloc(1);
	while (i < *(data->found_count))
	{
		expanded_result = ft_realloc(expanded_result, strlen(expanded_result), strlen(expanded_result) + strlen((*data->found_files)[i]) + 2);
		ft_strcat(expanded_result, (*data->found_files)[i]);
		if (i < *(data->found_count) - 1)
			ft_strcat(expanded_result, del);
		i++;
	}
	return (expanded_result);
}

char	*expand_wildcard_redir(char *pwd, int level, t_wildcard_data *data)
{
	int		i;
	char	*expanded_result;
	char	*del;

	del = gcalloc(2);
	wildcard(pwd, level, data);
	del[0] = *get_splitted_char(1);
	del[1] = '\0';
	if (*(data->found_count) == 0)
		return (ft_strdup(data->pattern[level]));
	i = 0;
	expanded_result = gcalloc(1);
	while (i < *(data->found_count))
	{
		expanded_result = ft_realloc(expanded_result, strlen(expanded_result), strlen(expanded_result) + strlen((*data->found_files)[i]) + 2);
		ft_strcat(expanded_result, (*data->found_files)[i]);
		if (i < *(data->found_count) - 1)
			ft_strcat(expanded_result, del);
		i++;
	}
	return (expanded_result);
}
