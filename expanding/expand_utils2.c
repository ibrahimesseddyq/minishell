/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:50:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 20:05:14 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambigious(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	get_var_length(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i + len] && !isspace(line[i + len])
		&& line[i + len] != '\'' && line[i + len] != '\"'
		&& line[i + len] != '/' && line[i + len] != '$' && line[i + len] != '=')
	{
		len++;
	}
	return (len);
}

void	append_char(t_expand_params *params, char c)
{
	int	old_size;

	old_size = 0;
	if (params->expanded_index >= params->expanded_size - 1)
	{
		old_size = params->expanded_size;
		params->expanded_size *= 2;
		params->expanded_line = ft_realloc
			(params->expanded_line, old_size, params->expanded_size);
	}
	params->expanded_line[params->expanded_index++] = c;
}

void	append_string(t_expand_params *params, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		append_char(params, str[j]);
		j++;
	}
}
