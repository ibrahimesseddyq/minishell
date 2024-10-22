/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:47:30 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 05:31:43 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	add_to_found(char ***found_files, int *found_count, const char *file)
{
	*found_files = ft_realloc(*found_files, (*found_count) * sizeof(char *),
			(*found_count + 1) * sizeof(char *));
	if (!(*found_files))
		return ;
	(*found_files)[*found_count] = gcalloc((strlen(file) + 1) * sizeof(char));
	if (!(*found_files)[*found_count])
		return ;
	ft_strcpy((*found_files)[*found_count], (char *)file);
	(*found_count)++;
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
		expanded_result = ft_realloc(expanded_result,
				ft_strlen(expanded_result), ft_strlen(expanded_result)
				+ ft_strlen((*data->found_files)[i]) + 2);
		ft_strcat(expanded_result, (*data->found_files)[i]);
		if (i < *(data->found_count) - 1)
			ft_strcat(expanded_result, del);
		i++;
	}
	printf("expanded wildcard[%s]\n", expanded_result);
	return (expanded_result);
}

void	convert_wd_to_splitting_char(t_wildcard_data *data)
{
	int		i;
	char	current_quote;

	i = 0;
	current_quote = 0;
	while (data->pattern[0][i])
	{
		if ((data->pattern[0][i] == '\'' || data->pattern[0][i] == '"')
			&& current_quote == '\0')
			current_quote = data->pattern[0][i];
		else if (data->pattern[0][i] == current_quote)
			current_quote = '\0';
		else if (data->pattern[0][i] == '*' && current_quote == '\0')
			data->pattern[0][i] = *get_splitted_char(4);
		i++;
	}
}

t_wd_redir_res	*expand_wildcard_redir(char *pwd, int level,
		t_wildcard_data *data)
{
	int				i;
	char			*expanded_result;
	char			*del;
	t_wd_redir_res	*res;

	res = gcalloc(sizeof(t_wd_redir_res));
	convert_wd_to_splitting_char(data);
	wildcard2(pwd, level, data, res);
	del = alloc_del();
	if (*(data->found_count) == 0)
		return (res->expanded_result = ft_strdup(data->pattern[level]),
			res->size = 1, res);
	i = 0;
	expanded_result = gcalloc(1);
	while (i < *(data->found_count))
	{
		expanded_result = ft_realloc(expanded_result,
				ft_strlen(expanded_result), ft_strlen(expanded_result)
				+ ft_strlen((*data->found_files)[i]) + 2);
		ft_strcat(expanded_result, (*data->found_files)[i]);
		if (i < *(data->found_count) - 1)
			ft_strcat(expanded_result, del);
		i++;
	}
	return (res->expanded_result = expanded_result, res);
}
