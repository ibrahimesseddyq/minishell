/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:48:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/28 08:07:34 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_variable_redir(t_expand_params *params, t_lst *env, char **line)
{
	int		varnamelen;
	char	*varname;
	char	*value;

	varnamelen = get_var_length(*line, params->i);
	value = NULL;
	// printf("[expand_variable_redir] varnamelen [%d] param->i [%d] and str is [%s]\n", varnamelen, params->i, (*line + params->i));
	varname = gcalloc(varnamelen + 1);
	ft_strlcpy(varname, *line + params->i, varnamelen + 1);
	if (params->i >= DEFAULT_NB - 1)
		handle_overflow();
	params->i += varnamelen;
	value = get_env(env, varname);
	// printf("[expand_variable_redir] varname [%s] value [%s] param->i [%d] varnamelen [%d]\n", varname, value, params->i, varnamelen);
	// printf("[expand_variable_redir] varname [%s] value [%s]\n", varname, value);
	if (!value)
	{
		if (check_ambigious(NULL))
			return (0);
		append_string(params, "");
		// printf("[expand_variable] variable value is [%s]\n", value);
	}
	else
	{
		value = ft_strdup(value);
		if (check_ambigious(value))
			return (0);
		append_string(params, value);
		// printf("[expand_variable] variable value is [%s]\n", value);
	}
	return (1);
}

int	expand_token_redir(t_expand_params *params, t_lst *env, char **line)
{
	if (params->i >= DEFAULT_NB - 1)
		handle_overflow();
	if ((*line)[params->i] == '$')
	{
		params->i++;
		if ((*line)[params->i] == '?')
		{
			expand_exit_status(params);
		}
		else
		{
			if (!expand_variable_redir(params, env, line))
				return (0);
		}
	}
	else
	{
		// printf("[expand_token_redir] char is [%d]\n", params->expanded_line[params->i]);
		append_char(params, (*line)[params->i++]);
	}
	return (1);
}

// tbdel f ft_redirection
char	*ft_expand_redir(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	while (line && line[params.i])
	{
		if (handle_quotes2(line[params.i], &params))
			continue ;
		if (!params.is_inside_quotes || params.current_quote == '\"')
		{
			if (!expand_token_redir(&params, env, &line))
				return (NULL);
		}
		else
		{
			append_char(&params, line[params.i++]);
		}
	}
	if (params.expanded_index >= DEFAULT_NB - 1)
		handle_overflow();
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
