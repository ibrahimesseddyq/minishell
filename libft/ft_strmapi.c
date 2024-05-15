/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:28:25 by ibes-sed          #+#    #+#             */
/*   Updated: 2023/12/01 16:16:27 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*index;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	index = (char *)malloc(sizeof(char) * len + 1);
	if (!index)
		return (NULL);
	while (i < len)
	{
		index[i] = f(i, s[i]);
		i++;
	}
	index[i] = '\0';
	return (index);
}
