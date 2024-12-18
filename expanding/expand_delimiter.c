/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:46:41 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 17:11:39 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_delimiter(char *line)
{
	char			*expanded_line;
	t_expand_params	params;

	expanded_line = gcalloc(DEFAULT_NB);
	params = init_params(expanded_line);
	while (line[params.i])
	{
		if (handle_quotes2(line[params.i], &params, line))
			continue ;
		if (!params.is_inside_quotes || (params.is_inside_quotes
				&& (params.current_quote == '\"'
					|| params.current_quote == '\'')))
		{
			if (params.is_inside_quotes && ft_isspace(line[params.i]))
			{
				expanded_line[params.expanded_index++] = line[params.i];
				params.i++;
			}
			append_char(&params, line[params.i++]);
		}
	}
	params.expanded_line[params.expanded_index] = '\0';
	params.expanded_line
		= skip_char(params.expanded_line, *get_splitted_char(3));
	return (params.expanded_line);
}
