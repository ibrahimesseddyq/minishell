/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:47:54 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/18 23:59:23 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable_heredoc(t_expand_params *params, t_lst *env)
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
	append_string(params, value);
}

void	expand_token_heredoc(t_expand_params *params, t_lst *env)
{
	if (params->expanded_line[params->i] == '$')
	{
		params->i++;
		expand_variable(params, env);
	}
	else
	{
		append_char(params, params->expanded_line[params->i++]);
	}
}

char	*ft_expand_heredoc(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(line, expanded_line);
	while (line[params.i])
	{
		if (!params.is_inside_quotes || params.current_quote == '\"')
		{
			expand_token(&params, env, line);
		}
		else
		{
			append_char(&params, line[params.i++]);
		}
	}
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
