/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/19 01:35:30 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s_expand_params
// {
//     int i;
//     int expanded_size;
//     int expanded_index;
//     int is_inside_quotes;
//     char current_quote;
//     char *expanded_line;
// } t_expand_params;


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

void	expand_token(t_expand_params *params, t_lst *env, char *line)
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
			expand_variable(params, env);
		}
	}
	else
	{
		printf("[expand_token] => [append_char]\n");
		append_char(params, line[params->i++]);
	}
}

char	*ft_expand(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(line, expanded_line);
	while (line[params.i])
	{
		handle_quotes2(line[params.i], &params);
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
