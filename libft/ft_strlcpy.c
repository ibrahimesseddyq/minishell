/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:27:36 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/20 04:51:28 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (len == 0)
		return (j);
	while (src[i] && i < len - 1)
	{
		dst[i] = src[i];
		printf("dst[%c] = src[%c] , %d < %d - 1(%d)\n", dst[i],src[i], i , len, len -1);
		i++;
	}
	dst[i] = '\0';
	return (j);
}
