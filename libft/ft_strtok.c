/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:15:48 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 17:36:27 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*stock;
	char		*start;

	if (str != NULL)
		stock = str;
	if (stock == NULL || *stock == '\0')
		return (NULL);
	while (*stock && ft_strchr(delim, *stock))
		stock++;
	if (*stock == '\0')
	{
		stock = NULL;
		return (NULL);
	}
	start = stock;
	while (*stock && !ft_strchr(delim, *stock))
		stock++;
	if (*stock)
	{
		*stock = '\0';
		stock++;
	}
	else
		stock = NULL;
	return (start);
}
