/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:33:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 05:42:29 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(int new_status, int mode)
{
	static int	status;

	if (mode == EXIT_PROGRAM)
	{
		exit(status);
	}
	else if (mode == GET_EXIT_STATUS)
		return (status);
	else if (mode == SET_EXIT_STATUS)
	{
		status = new_status;
	}
	return (status);
}

int builtins_state(int value, int builtin, int op)
{
	static t_builtins_state state;

	if (builtin == EXPORT_BUILTIN)
	{
		if (op == SET_BUILTIN)
			return (state.export_error = value, printf("set1\n"), value);
		else
			return (state.export_error);
	}
	else if (builtin == UNSET_BUILTIN)
	{
		if (op == SET_BUILTIN)
			return (state.unset_error = value,printf("set2 %d\n", value), value);
		else
			return (state.unset_error);	
	}
	return (UNKNOWN);
}

void	handle_overflow(void)
{
	write(2, "You aren't allowed to do that :)\n", 34);
	ft_exit(1, EXIT_PROGRAM);
}
