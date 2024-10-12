/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:11:55 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/12 13:30:18 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*next_token(t_tklist *token_list)
{
	if (token_list->curr_index < token_list->size)
	{
		return (&token_list->tokens[token_list->curr_index++]);
	}
	return (NULL);
}

void	set_beginning(t_tklist *token_list)
{
	token_list->curr_index = 0;
}

t_token	*peek_next_token(t_tklist *token_list, int offset)
{
	if ((token_list->curr_index + offset) < token_list->size)
	{
		return (&token_list->tokens[token_list->curr_index + offset]);
	}
	return (NULL);
}

int	should_stop(t_lexer *lexer, int in_quotes)
{
	return (!in_quotes && (ft_isspace(lexer->currentchar)
			|| lexer->currentchar == '|' || lexer->currentchar == '&'
			|| lexer->currentchar == ';' || lexer->currentchar == '('
			|| lexer->currentchar == ')' || lexer->currentchar == '>'
			|| lexer->currentchar == '<' || lexer->currentchar == '\n'));
}

char	*finalize_buffer(char *buffer, size_t i)
{
	char	*final_buffer;

	buffer[i] = '\0';
	final_buffer = (char *)ft_realloc
		(buffer, i * sizeof(char), (i + 1) * sizeof(char));
	if (final_buffer)
		return (final_buffer);
	else
		return (buffer);
}
