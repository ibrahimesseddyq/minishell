/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:48:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 02:18:19 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_itoa(int num)
{
	char	*str;
	int		temp_num;
	int		len;
	int		sign;

	(1) && (temp_num = num, len = 1, sign = 1);
	if (num < 0)
	{
		sign = -1;
		len++;
	}
	temp_num = num;
	while (temp_num != 0)
	{
		temp_num /= 10;
		len++;
	}
	(1) && (str = gcalloc(len + 1), str[len] = '\0');
	while (len--)
		(1) && (str[len] = (num % 10) * sign + '0', num /= 10);
	if (sign == -1)
		str[0] = '-';
	return (str);
}

t_expand_params	init_params(char *expanded_line)
{
	t_expand_params	params;

	params.i = 0;
	params.expanded_size = DEFAULT_NB;
	params.expanded_index = 0;
	params.is_inside_quotes = 0;
	params.current_quote = 0;
	params.expanded_line = expanded_line;
	return (params);
}

int	handle_quotes2(char c, t_expand_params *params)
{
	if ((c == '\'' || c == '\"') && !params->is_inside_quotes)
	{
		params->is_inside_quotes = 1;
		params->current_quote = c;
		params->i++;
		return (1);
	}
	else if (params->is_inside_quotes && c == params->current_quote)
	{
		params->is_inside_quotes = 0;
		params->current_quote = 0;
		params->i++;
		return (1);
	}
	return (0);
}

void	expand_exit_status(t_expand_params *params)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(ft_exit(4, GET_EXIT_STATUS));
	append_string(params, exit_status_str);
	params->i++;
}
