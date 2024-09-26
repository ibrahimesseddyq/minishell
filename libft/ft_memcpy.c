/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:17:32 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/25 20:42:13 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	unsigned char	*my_src;
// 	unsigned char	*my_dst;
// 	size_t			i;

// 	i = 0;
// 	if (!dst && !src)
// 		return (NULL);
// 	my_dst = (unsigned char *)dst;
// 	my_src = (unsigned char *)src;
// 	while (i < n)
// 	{
// 		my_dst[i] = my_src[i];
// 		i++;
// 	}
// 	return (dst);
// }


void		*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src;
	
	// printf("[memcpy]n [%zu], s1 [%s] s2[%s]\n", n, s1, s2);
	dest = (char*)s1;
	src = (char*)s2;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
