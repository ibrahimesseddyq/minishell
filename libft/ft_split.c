/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 01:22:32 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/08/13 18:29:25 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cnt);
}

static char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*new;

	i = 0;
	if (n == INT_MAX)
		return (NULL);
	new = (char *)malloc(n + 1);
	if (new == NULL)
		return (NULL);
	while (i < n)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		index;
	int		tail_matrice;
	char	**arr;

	index = -1;
	tail_matrice = count_words(s, c);
	arr = (char **)malloc((sizeof(char *)) * (tail_matrice + 1));
	if (!arr || tail_matrice == -1)
		return (NULL);
	while (++index < tail_matrice)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		while (*(s + i) != c && *(s + i))
			i++;
		arr[index] = ft_strndup(s, i);
		if (arr[index] == NULL)
			return (NULL);
		while (*s && *s != c)
			s++;
	}
	arr[index] = NULL;
	return (arr);
}
