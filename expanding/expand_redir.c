/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:48:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/18 22:14:31 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_variable_redir(t_expand_params *params, t_lst *env)
{
	int		varnamelen;
	char	*varname;
	char	*value;

	varnamelen = get_var_length(params->expanded_line, params->i);
	varname = gcalloc(varnamelen + 1);
	strncpy(varname, &params->expanded_line[params->i], varnamelen);
	varname[varnamelen] = '\0';
	params->i += varnamelen;
	value = ft_strdup(get_env(env, varname));
	if (check_ambigious(value))
		return (0);
	append_string(params, value);
	return (1);
}

int	expand_token_redir(t_expand_params *params, t_lst *env)
{
	if (params->expanded_line[params->i] == '$')
	{
		params->i++;
		if (params->expanded_line[params->i] == '?')
		{
			expand_exit_status(params);
		}
		else
		{
			if (!expand_variable_redir(params, env))
				return (0);
		}
	}
	else
	{
		append_char(params, params->expanded_line[params->i++]);
	}
	return (1);
}

// tbdel f ft_redirection
char	*ft_expand_redir(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(64);
	params = init_params(line, expanded_line);
	while (line[params.i])
	{
		handle_quotes2(line[params.i], &params);
		if (!params.is_inside_quotes || params.current_quote == '\"')
		{
			if (!expand_token_redir(&params, env))
				return (NULL);
		}
		else
		{
			append_char(&params, line[params.i++]);
		}
	}
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
