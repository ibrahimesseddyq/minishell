/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:15:48 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/21 16:21:51 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strtok(char *str, char sepa)
// {
// 	static char	*stock = NULL;
// 	char		*ptr;
// 	int		i;

// 	i = 0;
// 	ptr = NULL;
// 	if (str != NULL)
// 		stock = ft_strdup(str);
// 	while (*stock != '\0')
// 	{
// 		if (i == 0 && *stock != sepa)
// 		{
// 			i = 1;
// 			ptr = stock;
// 		}
// 		else if (i == 1 && *stock == sepa)
// 		{
// 			*stock = '\0';
// 			stock += 1;
// 			break ;
// 		}
// 		stock++;
// 	}
// 	return (ptr);
// }


char	*ft_strtok(char *str, const char *sepa)
{
	static char	*last;
	char		*token;
	size_t		sepa_len;

	if (str == NULL)
		str = last;
	if (str == NULL || *str == '\0')
		return (NULL);
	sepa_len = ft_strlen(sepa);
	token = str;
	while (*str)
	{
		if (ft_strncmp(str, sepa, sepa_len) == 0)
		{
			*str = '\0';
			last = str + sepa_len;
			return (token);
		}
		str++;
	}
	last = NULL;
	return (token);
}
