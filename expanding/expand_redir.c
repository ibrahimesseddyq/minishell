/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:48:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 20:08:14 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_variable_redir(t_expand_params *params, t_lst *env, char **line)
{
	int		varnamelen;
	char	*varname;
	char	*value;

	varnamelen = get_var_length(*line, params->i);
	(1) && (value = NULL, varname = gcalloc(varnamelen + 1));
	ft_strlcpy(varname, *line + params->i, varnamelen + 1);
	if (params->i >= DEFAULT_NB - 1)
		handle_overflow();
	params->i += varnamelen;
	value = get_env(env, varname);
	value = replace_star_outside_quotes(value);
	if (!value)
	{
		append_string(params, get_null_str());
	}
	else
	{
		value = ft_strdup(value);
		if (check_ambigious(value))
			return (0);
		append_string(params, value);
	}
	return (1);
}

int	expand_after_dollar_redir(t_expand_params *params,
		t_lst *env, char **line)
{
	if ((*line)[params->i + 1]
	&& is_not_a_charachter((*line)[params->i + 1])
	&& params->is_inside_quotes)
	{
		append_char(params, (*line)[params->i++]);
		return (1);
	}
	if (is_quote((*line)[params->i + 1]))
		return (handle_translation(params, env, line,
				return_array_of_2((*line)[params->i + 1], 0)));
	params->i++;
	if (!(*line)[params->i] || is_not_a_charachter((*line)[params->i]))
	{
		params->i--;
		append_char(params, (*line)[params->i++]);
	}
	if ((*line)[params->i] && is_not_a_charachter((*line)[params->i]))
		append_char(params, (*line)[params->i++]);
	else if ((*line)[params->i] == '?')
		expand_exit_status(params);
	else
		if (!expand_variable_redir(params, env, line))
			return (0);
	return (-1);
}

int	expand_token_redir(t_expand_params *params, t_lst *env, char **line)
{
	int	expand_dollar;

	if (params->i >= DEFAULT_NB - 1)
		handle_overflow();
	if ((*line)[params->i] == '$')
	{
		expand_dollar = expand_after_dollar_redir(params, env, line);
		if (expand_dollar != -1)
			return (expand_dollar);
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

char	*ft_expand_redir(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	while (line && line[params.i])
	{
		if (handle_quotes2(line[params.i], &params, line))
			continue ;
		if (!params.is_inside_quotes || params.current_quote == '\"')
		{
			if (!expand_token_redir(&params, env, &line))
				return (NULL);
		}
		else
			append_char(&params, line[params.i++]);
	}
	if (params.expanded_index >= DEFAULT_NB - 1)
		handle_overflow();
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
