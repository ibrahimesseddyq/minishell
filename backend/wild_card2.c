/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:55:38 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 22:03:45 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	match(char *pattern, const char *text)
{
	if (*pattern == '\0' && *text == '\0')
		return (1);
	if (*pattern == '*')
	{
		if (*(pattern + 1) == '\0')
			return (1);
		while (*text)
		{
			if (match(pattern + 1, text))
				return (1);
			text++;
		}
		return (match(pattern + 1, text));
	}
	if (*text != '\0' && (*pattern == *text))
		return (match(pattern + 1, text + 1));
	return (0);
}

char	**filterstrings(char *pattern
		, char *texts[], int numTexts, int *numMatches)
{
	char	**matches;
	int		i;

	*numMatches = 0;
	matches = malloc(numTexts * sizeof(char *));
	i = 0;
	if (!matches)
		return (NULL);
	while (i < numTexts)
	{
		if (match(pattern, texts[i]))
		{
			matches[*numMatches]
				= gcalloc((strlen(texts[i]) + 1) * sizeof(char));
			if (!matches[*numMatches])
				return (NULL);
			ft_strcpy(matches[*numMatches], texts[i]);
			(*numMatches)++;
		}
		i++;
	}
	return (matches);
}
