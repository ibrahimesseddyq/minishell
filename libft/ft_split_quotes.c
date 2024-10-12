/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:20:21 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/12 01:21:28 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static int	count_words(char *s, char c)
{
	t_count_word	state;

	(1) && (state.i = 0, state.cnt = 0,
		state.in_single_quote = 0, state.in_double_quote = 0);
	if (!s)
		return (-1);
	while (s[state.i])
	{
		while (s[state.i] == c && s[state.i])
			state.i++;
		if (s[state.i] && s[state.i] != c)
		{
			state.cnt++;
			while (s[state.i] && (state.in_single_quote
					|| state.in_double_quote || s[state.i] != c))
			{
				if (s[state.i] == '\'' && !state.in_double_quote)
					state.in_single_quote = !state.in_single_quote;
				else if (s[state.i] == '"' && !state.in_single_quote)
					state.in_double_quote = !state.in_double_quote;
				state.i++;
			}
		}
	}
	return (state.cnt);
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

void	check_in_quotes(char *s, t_split_quotes *state)
{
	if (s[state->word_length] == '\'' && !state->in_double_quote)
		state->in_single_quote = !state->in_single_quote;
	else if (s[state->word_length] == '"' && !state->in_single_quote)
		state->in_double_quote = !state->in_double_quote;
	state->word_length++;
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
			check_in_quotes(s, &state);
		}
		state.arr[state.index] = ft_strndup(s, state.word_length);
		if (state.arr[state.index] == NULL)
			return (NULL);
		s += state.word_length;
		state.index++;
	}
	return (state.arr[state.index] = NULL, state.arr);
}
