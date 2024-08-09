/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:23:26 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/08/03 10:13:26 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (*dest);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		len;

	len = ft_strlen(src) + 1;
	dest = (char *)malloc(len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}
