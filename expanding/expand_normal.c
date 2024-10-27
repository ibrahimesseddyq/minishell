/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/27 02:27:28 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable(t_expand_params *params,
			t_lst *env, char **line, int export_case)
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
		append_string(params, get_null_str());
	}
	else
	{
		value = ft_strdup(value);
		if (!export_case)
			if (!params->is_inside_quotes3)
				value = replace_space_with_second_separator(params, value);
		append_string(params, value);
	}
}

int	handle_translation(t_expand_params *params,
		t_lst *env, char **line, int *quote_export)
{
	params->i += 2;
	params->is_inside_quotes = 1;
	while ((*line)[params->i] && (*line)[params->i] != quote_export[0])
	{
		if ((*line)[params->i] == '$' && !(*line)[params->i + 1])
			break ;
		if ((*line)[params->i] == '$' && is_quote((*line)[params->i + 1]))
		{
			append_char(params, (*line)[params->i++]);
		}
		else if ((*line)[params->i] == '$'
			&& quote_export[0] != '\''
			&& !is_not_a_charachter((*line)[params->i + 1]))
		{
			params->i++;
			expand_variable(params, env, line, quote_export[1]);
		}
		else
			append_char(params, (*line)[params->i++]);
	}
	if ((*line)[params->i] == quote_export[0])
		params->i++;
	params->is_inside_quotes = 0;
	return (1);
}

int	expand_after_dollar(t_expand_params *params,
		t_lst *env, char **line, int export_case)
{
	if ((*line)[params->i + 1]
		&& is_not_a_charachter((*line)[params->i + 1])
		&& params->is_inside_quotes)
		return (append_char(params, (*line)[params->i++]), 1);
	if (is_quote((*line)[params->i + 1]))
		return (handle_translation(params, env, line,
				return_array_of_2((*line)[params->i + 1], export_case)));
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
		expand_variable(params, env, line, export_case);
	return (-1);
}

int	expand_token(t_expand_params *params, t_lst *env, char **line, char *cmd)
{
	int	export_case;
	int	expand_dollar;

	export_case = handle_export_case(line, cmd);
	if ((*line)[params->i] == '$')
	{
		expand_dollar = expand_after_dollar(params, env, line, export_case);
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

char	*ft_expand(char *line, t_lst *env, char *cmd)
{
	char			*expanded_line;
	t_expand_params	*params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	params->is_inside_quotes3 = 0;
	while (line && line[params->i])
	{
		if (handle_quotes2(line[params->i], &params, line))
			continue ;
		if (!params->is_inside_quotes || params->current_quote == '\"')
		{
			params->is_inside_quotes3 = params->is_inside_quotes;
			expand_token(params, env, &line, cmd);
		}
		else
		{
			append_char(params, line[params->i++]);
		}
	}
	params->expanded_line[params->expanded_index] = '\0';
	return (params->expanded_line);
}
