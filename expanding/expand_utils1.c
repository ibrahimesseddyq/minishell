/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:48:12 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/14 22:31:46 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	long	nbr;

	len = ft_numlen(n);
	nbr = n;
	s = (char *)gcalloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (nbr == 0)
		s[0] = '0';
	if (nbr < 0)
	{
		s[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		s[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (s);
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
	// printf("exit status is [%s]\n", exit_status_str);
	append_string(params, exit_status_str);
	params->i++;
}
