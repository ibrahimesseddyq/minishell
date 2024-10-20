/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 16:59:24 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	expand_variable(t_expand_params *params, t_lst *env, char **line)
{
	int		varnamelen;
	char	*varname;
	char	*value;

	varnamelen = get_var_length(*line, params->i);
	varname = gcalloc(varnamelen + 1);
	ft_strncpy(varname, *line + params->i, varnamelen);
	varname[varnamelen] = '\0';
	params->i += varnamelen;
	value = get_env(env, varname);
	value = replace_star_outside_quotes(value);
	if (!value)
	{
		append_string(params, "");
	}
	else
	{
		value = ft_strdup(value);
		if (!params->is_inside_quotes3)
			value = replace_space_with_second_separator(params, value);
		append_string(params, value);
	}
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

int	expand_token(t_expand_params *params, t_lst *env, char **line)
{
	if ((*line)[params->i] == '$')
	{
		if ((((*line)[params->i + 1] == '\''
				|| (*line)[params->i + 1] == '"'
			|| ft_isspace((*line)[params->i + 1]))
				&& params->is_inside_quotes) || !(*line)[params->i + 1]
					|| ((*line)[params->i + 1]
					&& is_not_a_charachter((*line)[params->i + 1])))
			return (append_char(params, (*line)[params->i++]), 1);
		params->i++;
		if (((*line)[params->i] && is_not_a_charachter((*line)[params->i])))
			append_char(params, (*line)[params->i++]);
		else if ((*line)[params->i] == '?')
			expand_exit_status(params);
		else
			expand_variable(params, env, line);
	}
	else if ((*line)[params->i] == '*' && !params->is_inside_quotes)
	{
		(*line)[params->i] = *get_splitted_char(4);
		append_char(params, (*line)[params->i++]);
	}
	else
		append_char(params, (*line)[params->i++]);
	return (1);
}

char	*ft_expand(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	params.is_inside_quotes3 = 0;
	while (line && line[params.i])
	{
		if (handle_quotes2(line[params.i], &params))
			continue ;
		if (!params.is_inside_quotes || params.current_quote == '\"')
		{
			params.is_inside_quotes3 = params.is_inside_quotes;
			expand_token(&params, env, &line);
		}
		else
		{
			append_char(&params, line[params.i++]);
		}
	}
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
