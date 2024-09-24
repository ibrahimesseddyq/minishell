/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:50 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 03:05:49 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	analyse_syntax(t_tklist *list)
{
	char		*final_token;
	int			curr_token;
	t_token		*token;
	int			parentheses;
	int			e;
	static int	tr[9][11]
		= {{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
	{-1, -1, 4, 8, 7, 6, 3, 3, 3, 3, 2},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2},
	{-1, -1, 4, 8, 7, 6, 5, 5, 5, 5, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2}};

	parentheses = 0;
	e = 0;
	token = NULL;
	curr_token = next_token(list)->type;
	if (!curr_token)
		return (0);
	if (curr_token == TK_LPR)
		parentheses++;
	while (tr[e][curr_token] != -1 && curr_token > 0)
	{
		e = tr[e][curr_token];
		token = next_token(list);
		curr_token = token->type;
		final_token = token->value;
		if (curr_token == TK_LPR)
			 parentheses++;
		if (curr_token == TK_RPR)
		{
			if (parentheses > 0)
				parentheses--;
			else 
				curr_token = -1;
		}
	}
	// printf("end - curr token %d parentheses %d and e %d\n",curr_token, parentheses, e);
	if (curr_token == 0 && parentheses == 0 && (e == 2 || e == 4))
		return (1);
	else
		return (write(2, "syntax error near unexpected token `%s'\n"
			, 41), write(2, final_token, ft_strlen(final_token))
			, write(2, "\n", 1), 0);
}