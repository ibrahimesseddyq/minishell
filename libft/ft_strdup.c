/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:23:26 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/12 00:03:14 by ibes-sed         ###   ########.fr       */
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

	if (!src)
	{
		dest = (char *)gcalloc(1 * sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	len = ft_strlen(src) + 1;
	dest = (char *)gcalloc(len * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}

char	*ft_strdup3(char *src)
{
	char	*dest;
	int		len;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	dest = (char *)gcalloc(len * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}
