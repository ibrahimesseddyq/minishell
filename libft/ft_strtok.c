/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:15:48 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 18:16:25 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char sepa)
{
	char	*ptr;
	char	*end;

	end = NULL;
	ptr = NULL;
	if (str == NULL)
		return (NULL);
	while (*str == sepa)
		str++;
	if (*str == '\0')
		return (NULL);
	ptr = str;
	end = ft_strchr(str, sepa);
	if (end != NULL)
		*end = '\0';
	return (ptr);
}
