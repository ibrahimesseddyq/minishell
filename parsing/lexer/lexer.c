/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:06:35 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 15:46:11 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)gcalloc(sizeof(t_lexer));
	lexer->input = input;
	lexer->pos = 0;
	lexer->currentchar = input[lexer->pos];
	return (lexer);
}

void	advance(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos >= (int)ft_strlen(lexer->input))
	{
		lexer->currentchar = '\0';
	}
	else
	{
		lexer->currentchar = lexer->input[lexer->pos];
	}
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->currentchar != '\0'
		&& (isspace(lexer->currentchar)
			|| lexer->currentchar == '\n'))
	{
		advance(lexer);
	}
}

t_tklist	*tokenize(char *input)
{
	t_lexer		*lexer;
	t_tklist	*token_list;
	t_token		*token;

	lexer = init_lexer(input);
	token_list = (t_tklist *)gcalloc(sizeof(t_tklist));
	token = get_next_token(lexer);
	token_list->tokens = NULL;
	token_list->curr_index = 0;
	token_list->size = 0;
	while (token->type != TOKEN_EOF)
	{
		token_list->size++;
		token_list->tokens = (t_token *)ft_realloc
			(token_list->tokens, (token_list->size - 1) * sizeof(t_token),
				token_list->size * sizeof(t_token));
		token_list->tokens[token_list->size - 1] = *token;
		token = get_next_token(lexer);
	}
	token_list->size++;
	token_list->tokens = (t_token *)ft_realloc
		(token_list->tokens, (token_list->size - 1) * sizeof(t_token),
			token_list->size * sizeof(t_token));
	token_list->tokens[token_list->size - 1] = *token;
	return (token_list);
}

t_token	*peek_token(t_tklist *token_list)
{
	if (token_list->curr_index < token_list->size)
	{
		return (&token_list->tokens[token_list->curr_index]);
	}
	return (NULL);
}
