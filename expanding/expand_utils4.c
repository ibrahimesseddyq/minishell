/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:09:13 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 20:08:46 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_export_case(char **line, char *cmd)
{
	if (!ft_strcmp(cmd, "export") && check_valid_export(*line)
		&& (ft_strchr(*line, '=') < ft_strchr(*line, '$')))
	{
		return (1);
	}
	return (0);
}

int	next_empty_string(char *line, t_expand_params *params, char quote)
{
	if (line[params->i] == quote && line[params->i + 1] == quote)
		return (1);
	return (0);
}

int	is_not_a_charachter(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (0);
	if (c >= 'a' && c <= 'z')
		return (0);
	if (c == '_' || c == '?')
		return (0);
	return (1);
}

char	*replace_star_outside_quotes(const char *input)
{
	size_t	len;
	char	*result;
	bool	in_quotes;
	size_t	i;

	if (input == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(input);
	result = (char *)gcalloc(len + 1);
	if (result == NULL)
		return (NULL);
	in_quotes = false;
	while (i < len)
	{
		if (input[i] == '"')
			(1) && (in_quotes = !in_quotes, result[i] = input[i]);
		else if (input[i] == '*' && !in_quotes)
			result[i] = *get_splitted_char(4);
		else
			result[i] = input[i];
		i++;
	}
	return (result[len] = '\0', result);
}

int	*return_array_of_2(int a, int b)
{
	int	*array;

	array = gcalloc(2 * sizeof(int));
	array[0] = a;
	array[1] = b;
	return (array);
}
