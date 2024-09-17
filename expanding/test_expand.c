/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 12:47:03 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void	expand_variable(t_expand_params *params, t_lst *env)
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
	if (params->expanded_index >= params->expanded_size - 1)
	{
		params->expanded_size *= 2;
		params->expanded_line
			= realloc(params->expanded_line, params->expanded_size);
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

char	*ft_expand(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(64);
	params = init_params(line, expanded_line);
	while (line[params.i])
	{
		handle_quotes(line[params.i], &params);
		if (!params.is_inside_quotes || params.current_quote == '\"')
		{
			expand_token(&params, env);
		}
		else
		{
			append_char(&params, line[params.i++]);
		}
	}
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
