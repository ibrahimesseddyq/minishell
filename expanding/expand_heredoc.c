/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:47:54 by ibes-sed          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/06 19:59:53 by ibes-sed         ###   ########.fr       */
=======
/*   Updated: 2024/10/06 16:20:42 by ynachat          ###   ########.fr       */
>>>>>>> dfe972dee838b74ef85a77f2f8237ae47c2d66e9
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variable_heredoc(t_expand_params *params,
			t_lst *env, char **line)
{
	int		varnamelen;
	char	*varname;
	char	*value;

	varnamelen = get_var_length(*line, params->i);
	varname = gcalloc(varnamelen + 1);
	strncpy(varname, *line + params->i, varnamelen);
	varname[varnamelen] = '\0';
	params->i += varnamelen;
	value = get_env(env, varname);
	if (!value)
	{
		if (check_ambigious(NULL))
			return ;
		append_string(params, "");
	}
	else
	{
		value = ft_strdup(value);
		if (check_ambigious(value))
			return ;
		append_string(params, value);
	}
}

void	expand_token_heredoc(t_expand_params *params, t_lst *env, char **line)
{
	if ((*line)[params->i] == '$')
	{
		params->i++;
		expand_variable_heredoc(params, env, line);
	}
	else
	{
		append_char(params, (*line)[params->i++]);
	}
}

char	*ft_expand_heredoc(char *line, t_lst *env)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	while (line[params.i])
	{
		expand_token_heredoc(&params, env, &line);
	}
	params.expanded_line[params.expanded_index] = '\0';
	return (params.expanded_line);
}
