/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:04:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2023/11/23 17:03:23 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_count(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	char		*str;
	long		num;
	int			i;

	num = (long)nbr;
	i = ft_count(nbr);
	str = (char *)malloc(sizeof(char) * (ft_count(nbr) + 1));
	if (!str)
		return (NULL);
	if (num == 0)
	{
		str[0] = 48;
	}
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	str[i] = '\0';
	while (num > 0)
	{
		str[--i] = (num % 10) + 48;
		num = num / 10;
	}
	return (str);
}
