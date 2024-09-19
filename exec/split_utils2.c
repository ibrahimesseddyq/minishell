/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:19:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/18 22:39:09 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*get_splitted_char(int index)
{
	static char	c[3];
	if (c[index - 1] == 0)
		c[index - 1] = 33;
	// printf("string %c %c , got c %c\n", c[0], c[1] , c[index - 1]);
	// printf("get add = %p\n",&c[index - 1]);
	return (&c[index - 1]);
}
