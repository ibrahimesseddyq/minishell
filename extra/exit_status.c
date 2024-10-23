/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:33:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 04:01:42 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(int new_status, int mode)
{
	static int	status;

	if (mode == EXIT_PROGRAM)
	{
		exit(new_status);
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
	gc_free_all();
	ft_exit(1, EXIT_PROGRAM);
}
