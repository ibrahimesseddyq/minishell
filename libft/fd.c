/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:55:44 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/27 02:24:28 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_fd(void)
{
	int	i;

	i = 3;
	while (i < OPEN_MAX)
	{
		ft_close(&i);
		i++;
	}
}

int	ft_close(int *fd)
{
	int	ret;

	if (fd)
	{
		if (*fd < 0)
			return (0);
		ret = close(*fd);
		*fd = -1;
	return (ret);
	}
	return (-1);
}
