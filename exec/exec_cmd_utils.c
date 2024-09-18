/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:06:17 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 21:59:31 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_export_errors(char *str)
{
	if (!str || is_num(str[0]) || str[0] == '='
		|| !str[0] || ft_strcmp(str, "\"\"") == 0
		|| ft_strcmp(str, "\'\'") == 0)
		return (1);
	return (0);
}

char	*char_to_string(char c)
{
	char	*str;

	str = gcalloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
