/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:19:47 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 02:19:42 by ynachat          ###   ########.fr       */
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
char	*replace_space_with_second_separator(t_expand_params *params, char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = gcalloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !params->is_inside_quotes2)
			params->is_inside_quotes2 = 1;
		else if ((str[i] == '\'' || str[i] == '\"')
			&& params->is_inside_quotes2)
			params->is_inside_quotes2 = 0;
		// printf("[replace_space_with_second_separator] str [%s]  is inside quotes [%d]\n",str, params->is_inside_quotes);
		if (str[i] == ' ' && !params->is_inside_quotes2)
			res[i] = *get_splitted_char(2);
		else
			res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	expand_variable(t_expand_params *params, t_lst *env, char **line)
{
	int		varnamelen;
	char	*varname;
	char	*value;

	varnamelen = get_var_length(*line, params->i);
	// printf("[expand_variable] varnamelen [%d] param->i [%d]  and char is [%c]\n", varnamelen, params->i, *(*line + params->i));
	varname = gcalloc(varnamelen + 1);
	strncpy(varname, *line + params->i, varnamelen);
	varname[varnamelen] = '\0';
	params->i += varnamelen;
	value = get_env(env, varname);
	if (!value)
	{
		append_string(params, "");
		// printf("[expand_variable] variable value is [%s]\n", value);
	}
	else
	{
		value = ft_strdup(value);
		value = replace_space_with_second_separator(params, value);
		append_string(params, value);
	}
}

void	expand_token(t_expand_params *params, t_lst *env, char **line)
{
	if ((*line)[params->i] == '$')
	{
		params->i++;
		if ((*line)[params->i] == '?')
		{
			expand_exit_status(params);
		}
		else
		{
			expand_variable(params, env, line);
		}
	}
	else
	{
		append_char(params, (*line)[params->i++]);
	}
}

char	*ft_expand(char *line, t_lst *env)
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
