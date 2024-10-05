/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:46:41 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/05 10:59:03 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	expand_variable_redir(t_expand_params *params, t_lst *env)
// {
// 	int		varnamelen;
// 	char	*varname;
// 	char	*value;

// 	varnamelen = get_var_length(params->expanded_line, params->i);
// 	varname = gcalloc(varnamelen + 1);
// 	strncpy(varname, &params->expanded_line[params->i], varnamelen);
// 	varname[varnamelen] = '\0';
// 	params->i += varnamelen;
// 	value = ft_strdup(get_env(env, varname));
// 	if (check_ambigious(value))
// 		return (0);
// 	append_string(params, value);
// 	return (1);
// }

// int	expand_token_delimiter(t_expand_params *params, t_lst *env)
// {
// 	if (params->expanded_line[params->i] == '$')
// 	{
// 		params->i++;
// 		if (params->expanded_line[params->i] == '?')
// 		{
// 			expand_exit_status(params);
// 		}
// 		else
// 		{
// 			if (!expand_variable_redir(params, env))
// 				return (0);
// 		}
// 	}
// 	else
// 	{
// 		append_char(params, params->expanded_line[params->i++]);
// 	}
// 	return (1);
// }

// void	handle_quotes2(char c, t_expand_params *params)
// {
// 	if ((c == '\'' || c == '\"') && !params->is_inside_quotes)
// 	{
// 		params->is_inside_quotes = 1;
// 		params->current_quote = c;
// 		params->i++;
// 	}
// 	else if (params->is_inside_quotes && c == params->current_quote)
// 	{
// 		params->is_inside_quotes = 0;
// 		params->current_quote = 0;
// 		params->i++;
// 	}
// }

// tbdel f ft_redirection
char	*ft_expand_delimiter(char *line)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	// printf("delimiter is [%s]\n", line);
	while (line[params.i])
	{
		if (handle_quotes2(line[params.i], &params))
			continue ;
		if (!params.is_inside_quotes || (params.is_inside_quotes
				&& (params.current_quote == '\"'
					|| params.current_quote == '\'')))
		{
			if (params.is_inside_quotes && line[params.i] == ' ')
			{
				expanded_line[params.expanded_index++] = ' ';
				params.i++;
			}
			append_char(&params, line[params.i++]);
		}
	}
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
