/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:19:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/14 22:46:04 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*get_splitted_char(int index)
{
	static char	c[3];

	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	if (c[index - 1] == 0)
		c[index - 1] = 33;
	return (&c[index - 1]);
}
