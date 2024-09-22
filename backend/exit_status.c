/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:33:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 01:38:09 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(int new_status, int mode)
{
	static int	status;

	status = 0;
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

void	handle_overflow(void)
{
	write(2, "You aren't allowed to do that :)\n", 34);
	ft_exit(1, EXIT_PROGRAM);
}
