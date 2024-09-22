/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:39:10 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 02:59:33 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_l_redir(t_lexer *lexer)
{
	t_token	*token;

	advance(lexer);
	if (lexer->currentchar == '<')
	{
		advance(lexer);
		token = (t_token *)gcalloc(sizeof(t_token));
		token->type = TK_LESSERTHAN2;
		token->value = ft_strdup("<<");
		return (token);
	}
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_LESSERTHAN1;
	token->value = ft_strdup("<");
	return (token);
}

t_token	*token_word(t_lexer *lexer)
{
	t_token	*token;
	char	*word;

	word = get_word(lexer);
	// printf("	[token_word] word is [%s]\n", word);
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_WORD;
	token->value = word;
	return (token);
}

t_token	*token_illegal(t_lexer *lexer)
{
	t_token	*token;	
	char	unrecognized[2];

	unrecognized[0] = lexer->currentchar;
	unrecognized[1] = '\0';
	advance(lexer);
	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TK_ILLEGAL;
	token->value = ft_strdup(unrecognized);
	return (token);
}

t_token	*token_eof(void)
{
	t_token	*token;

	token = (t_token *)gcalloc(sizeof(t_token));
	token->type = TOKEN_EOF;
	token->value = strdup("EOF");
	return (token);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->currentchar != '\0')
	{
		if (isspace(lexer->currentchar) || lexer->currentchar == '\n')
		{
			skip_whitespace(lexer);
			continue ;
		}
		if (lexer->currentchar == '|')
			return (token_pipe(lexer));
		if (lexer->currentchar == '&')
			return (token_and(lexer));
		if (lexer->currentchar == '(')
			return (token_opening_parenthesis(lexer));
		if (lexer->currentchar == ')')
			return (token_opening_parenthesis(lexer));
		if (lexer->currentchar == '>')
			return (token_r_redir(lexer));
		if (lexer->currentchar == '<')
			return (token_l_redir(lexer));
		if (ft_isalnum(lexer->currentchar)
			|| ft_strchr(WORD, lexer->currentchar))
			return (token_word(lexer));
		return (token_illegal(lexer));
	}
	return (token_eof());
}
