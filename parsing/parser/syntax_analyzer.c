/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/08 14:58:04 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_syntax_error(char *final_token)
{
	write(2, "syntax error unexpected token ", 31);
	if (final_token)
		write(2, final_token, ft_strlen(final_token));
	write(2, "\n", 1);
}

static int	process_token(int *parentheses, t_token **token)
{
	int	curr_token;

	curr_token = (*token)->type;
	if (curr_token == TK_LPR)
		(*parentheses)++;
	else if (curr_token == TK_RPR)
	{
		if (*parentheses > 0)
			(*parentheses)--;
		else
			return (-1);
	}
	return (curr_token);
}

static int	process_tokens(t_tklist *list, int (*tr)[11], char **final_token)
{
	int		curr_token;
	t_token	*token;
	int		parentheses;
	int		e;

	initialize_analyzer(final_token, &parentheses, &token, &e);
	curr_token = next_token(list)->type;
	if (!curr_token)
		return (1);
	if (curr_token == TK_LPR)
		parentheses++;
	while (tr[e][curr_token] != -1 && curr_token > 0)
	{
		e = tr[e][curr_token];
		token = next_token(list);
		*final_token = token->value;
		curr_token = process_token(&parentheses, &token);
	}
	return (curr_token == 0 && parentheses == 0 && (e == 2 || e == 4));
}

int	analyse_syntax(t_tklist *list)
{
	char	*final_token;
	int		(*tr)[11];
	int		result;

	tr = get_matrix();
	result = process_tokens(list, tr, &final_token);
	if (!result)
		print_syntax_error(final_token);
	return (result);
}
