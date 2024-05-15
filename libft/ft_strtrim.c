/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 02:25:45 by ibes-sed          #+#    #+#             */
/*   Updated: 2023/11/23 17:19:40 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const	*s1, char const	*set)
{
	char		*str;
	size_t		front;
	size_t		rear;

	if (!s1 || !set)
		return (NULL);
	front = 0;
	rear = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (rear > front && s1[rear - 1] && ft_strchr(set, s1[rear - 1]))
		rear--;
	str = (char *)malloc(sizeof(char) * (rear - front + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[front], rear - front + 1);
	return (str);
}
