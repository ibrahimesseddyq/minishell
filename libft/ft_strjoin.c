/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:24:15 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/08/15 18:31:20 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copystring(char *newstr, const char *s2, int totalsize, int i)
{
	int	x;

	x = 0;
	while (i < totalsize)
	{
		newstr[i++] = s2[x++];
	}
	newstr[i] = '\0';
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*newstr;
	size_t	totalsize;
	size_t	i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	totalsize = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)gcalloc((sizeof(char) * totalsize + 1));
	if (newstr == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		newstr[i] = s1[i];
		i++;
	}
	copystring(newstr, s2, totalsize, i);
	return (newstr);
}
