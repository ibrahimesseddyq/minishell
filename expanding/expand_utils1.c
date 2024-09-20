/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:48:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/20 05:09:36 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_itoa(int num)
{
	char	*str;
	int		temp_num;
	int		len;
	int		sign;

	temp_num = num;
	len = 1;
	sign = 1;
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
	str = gcalloc(len + 1);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (num % 10) * sign + '0';
		num /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

t_expand_params	init_params(char *line, char *expanded_line)
{
	t_expand_params	params;

	params.i = 0;
	params.expanded_size = 64;
	params.expanded_index = 0;
	params.is_inside_quotes = 0;
	params.current_quote = 0;
	params.expanded_line = expanded_line;
	return (params);
}
// if ((start[i] == '\'' || start[i] == '\"') && !is_inside_quotes)
//         {
//             is_inside_quotes = 1;
//             // printf("set inside quote\n");
//             current_quote = start[i];
//             i++;
//             continue;
//         }
//         else if (is_inside_quotes && start[i] == current_quote)
//         {
//              if (start[i] == '\"' && is_inside_quotes && current_quote == '\"' && start[i - 1] == '$')
//             {
//                         // printf("dkhl\n");
//                         expanded_line[expanded_index++] = '$';

//             }
//             // printf("unset inside quote\n");
//             is_inside_quotes = 0;
//             current_quote = 0;
//             i++;  // Skip the closing quote
//             continue;
//         }
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
