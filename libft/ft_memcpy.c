/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:17:32 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/08/22 20:40:53 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*my_src;
	unsigned char	*my_dst;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	my_dst = (unsigned char *)dst;
	my_src = (unsigned char *)src;
	// printf("dst %s\n", dst);
	// printf("src %s\n", src);
	// printf("my_dst len %lu\n", strlen(dst));
	// printf("n %zu\n", n);
	while (i < n)
	{
		// printf("i %zu\n", i);
		my_dst[i] = my_src[i];
		i++;
	}
	return (dst);
}
