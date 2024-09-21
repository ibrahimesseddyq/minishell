/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:12:03 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/21 05:49:38 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_word(t_lexer *lexer)
{
	size_t			buffer_size;
	char			*result;
	size_t			i;
	t_quote_state	*quotes;

	
	quotes = malloc(sizeof(t_quote_state));
	if (!quotes) {
		perror("malloc failed");
		return NULL;  // or handle the error appropriately
	}
	quotes->in_quotes = 0;
	quotes->quote_char = '\0';
	i = 0;
	buffer_size = INITIAL_BUFFER_SIZE;
	result = allocate_buffer(buffer_size);
	while (lexer->currentchar != '\0')
	{
		if (i >= buffer_size - 1)
			result = resize_buffer(result, &buffer_size);
		if (handle_quotes(lexer, quotes, result, &i))
			continue ;
		if (handle_escaped_characters(lexer, result, &i))
			continue ;
		if (should_stop(lexer, quotes->in_quotes))
			break ;
		result[i++] = lexer->currentchar;
		// printf("		[get_word] lexer current char is [%c]\n", lexer->currentchar);
		advance(lexer);
	}
	return (finalize_buffer(result, i));
}

char	*allocate_buffer(size_t buffer_size)
{
	return ((char *)gcalloc(buffer_size * sizeof(char)));
}

char	*resize_buffer(char *buffer, size_t *buffer_size)
{
	char	*new_buffer;

	*buffer_size *= BUFFER_GROWTH_FACTOR;
	new_buffer = (char *)realloc(buffer, (*buffer_size) * sizeof(char));
	if (new_buffer)
		return (new_buffer);
	else
		return (buffer);
}

int	handle_quotes(t_lexer *lexer
	, t_quote_state *quote_state, char *result, size_t *i)
{
	if (!quote_state->in_quotes
		&& (lexer->currentchar == '"' || lexer->currentchar == '\''))
	{
		quote_state->in_quotes = 1;
		quote_state->quote_char = lexer->currentchar;
		result[(*i)++] = lexer->currentchar;
		advance(lexer);
		return (1);
	}
	else if (quote_state->in_quotes
		&& lexer->currentchar == quote_state->quote_char)
	{
		quote_state->in_quotes = 0;
		result[(*i)++] = lexer->currentchar;
		advance(lexer);
		return (1);
	}
	return (0);
}

int	handle_escaped_characters(t_lexer *lexer, char *result, size_t *i)
{
	if (lexer->currentchar == '\\')
	{
		result[(*i)++] = lexer->currentchar;
		advance(lexer);
		if (lexer->currentchar != '\0')
		{
			result[(*i)++] = lexer->currentchar;
			advance(lexer);
		}
		return (1);
	}
	return (0);
}
