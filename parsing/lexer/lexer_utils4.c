/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:05:16 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 17:05:17 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_pipe(t_lexer *lexer)
{
	t_token	*token;

	advance(lexer);
	if (lexer->currentchar == '|')
	{
		advance(lexer);
		token = (t_token *)gcalloc(sizeof(t_token));
		token->type = TK_OR;
		token->value = ft_strdup("||");
		return (token);
	}
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_PIPE;
	token->value = ft_strdup("|");
	return (token);
}

t_token	*token_and(t_lexer *lexer)
{
	t_token	*token;

	advance(lexer);
	if (lexer->currentchar == '&')
	{
		advance(lexer);
		token = (t_token *)gcalloc(sizeof(t_token));
		token->type = TK_AND;
		token->value = ft_strdup("&&");
		return (token);
	}
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_ILLEGAL;
	token->value = ft_strdup("");
	return (token);
}

t_token	*token_opening_parenthesis(t_lexer *lexer)
{
	t_token	*token;

	advance(lexer);
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_LPR;
	token->value = ft_strdup("(");
	return (token);
}

t_token	*token_closing_parenthesis(t_lexer *lexer)
{
	t_token	*token;

	advance(lexer);
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_RPR;
	token->value = ft_strdup(")");
	return (token);
}

t_token	*token_r_redir(t_lexer *lexer)
{
	t_token	*token;

	advance(lexer);
	if (lexer->currentchar == '>')
	{
		advance(lexer);
		token = (t_token *)gcalloc(sizeof(t_token));
		token->type = TK_GREATERTHAN2;
		token->value = ft_strdup(">>");
		return (token);
	}
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_GREATERTHAN1;
	token->value = ft_strdup(">");
	return (token);
}
