/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:27:36 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/28 02:24:38 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (len == 0)
		return (j);
	while (src[i] && i < len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

char    *ft_strcpy(char *s1, char *s2)
  {
      int i;
 
      i = 0;
      while (s2[i])
      {
          s1[i] = s2[i];
          i++;
      }
      s1[i] = s2[i];
      return (s1);
  }