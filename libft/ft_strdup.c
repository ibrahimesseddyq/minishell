/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:23:26 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/12 21:05:52 by ynachat          ###   ########.fr       */
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

char *ft_strdup(char *src)
{
    char *dest;
    int len;
	// printf("[%s]\n", src);
    if (!src )
    {
        dest = (char *)gcalloc(1 * sizeof(char)); // Allocate memory for an empty string
        if (!dest)
            return (NULL);
        dest[0] = '\0'; // Null-terminate the empty string
        return dest;
    }

    len = ft_strlen(src) + 1; // Include space for the null-terminator
    dest = (char *)gcalloc(len * sizeof(char));
    if (!dest)
        return (NULL);

    ft_strcpy(dest, src); // Copy the string
    return dest;
}

