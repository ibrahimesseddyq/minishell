/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:19:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 02:42:31 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_splitted_char(int index)
{
	static char	c[3];

	if (c[index - 1] == 0)
		c[index - 1] = 33;
	// printf("string %c %c , got c %c\n", c[0], c[1] , c[index - 1]);
	// printf("get add = %p\n",&c[index - 1]);
	return (&c[index - 1]);
}
