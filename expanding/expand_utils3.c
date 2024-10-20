/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:22:37 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 15:32:20 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_space_with_second_separator(t_expand_params *params, char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = gcalloc(ft_strlen(str) + 1);
	params->is_inside_quotes2 = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !params->is_inside_quotes2)
		{
			params->is_inside_quotes2 = 1;
		}
		else if ((str[i] == '\'' || str[i] == '\"')
			&& params->is_inside_quotes2)
			params->is_inside_quotes2 = 0;
		if (ft_isspace(str[i]) && !params->is_inside_quotes2)
			res[i] = *get_splitted_char(2);
		else
			res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	append_dollar_redir(t_expand_params *params, char **line)
{
	if ((((*line)[params->i + 1] == '\''
			|| (*line)[params->i + 1] == '"'
		|| ft_isspace((*line)[params->i + 1]))
		&& params->is_inside_quotes) || !(*line)[params->i + 1]
		|| ((*line)[params->i + 1]
		&& is_not_a_charachter((*line)[params->i + 1])))
		return (1);
	return (0);
}
