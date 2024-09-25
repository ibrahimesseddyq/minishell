/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:20:21 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/26 00:09:20 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	cnt;
	int	in_single_quote;
	int	in_double_quote;

	(1) && (i = 0, cnt = 0, in_single_quote = 0, in_double_quote = 0);
	if (!s)
		return (-1);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
		{
			cnt++;
			while (s[i] && (in_single_quote || in_double_quote || s[i] != c))
			{
				if (s[i] == '\'' && !in_double_quote)
					in_single_quote = !in_single_quote;
				else if (s[i] == '"' && !in_single_quote)
					in_double_quote = !in_double_quote;
				i++;
			}
		}
	}
	return (cnt);
}

static int	initialize_vars_state(t_split_quotes *state, char *s, char c)
{
	state->index = 0;
	state->in_single_quote = 0;
	state->in_double_quote = 0;
	state->tail_matrice = count_words(s, c);
	state->arr = (char **)gcalloc((sizeof(char *)) * (state->tail_matrice + 1));
	if (!state->arr || state->tail_matrice == -1)
		return (0);
	return (1);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)gcalloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_split_quotes(char *s, char c)
{
	t_split_quotes	state;

	if (initialize_vars_state(&state, s, c) == 0)
		return (NULL);
	while (state.index < state.tail_matrice)
	{
		state.i = 0;
		while (*s && *s == c)
			s++;
		state.word_length = 0;
		while (s[state.word_length]
			&& (state.in_single_quote || state.in_double_quote
				|| s[state.word_length] != c))
		{
			if (s[state.word_length] == '\'' && !state.in_double_quote)
				state.in_single_quote = !state.in_single_quote;
			else if (s[state.word_length] == '"' && !state.in_single_quote)
				state.in_double_quote = !state.in_double_quote;
			state.word_length++;
		}
		state.arr[state.index] = ft_strndup(s, state.word_length);
		if (state.arr[state.index] == NULL)
			return (NULL);
		s += state.word_length;
		state.index++;
	}
	return (state.arr[state.index] = NULL, state.arr);
}
