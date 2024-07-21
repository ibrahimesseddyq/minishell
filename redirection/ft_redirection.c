/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/21 16:03:22 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int ft_redirection(t_redir_list *io, t_astnode *ast)
{
	while (io)
	{
		if (io->redir->type == NODE_REDIRECT_OUT || io->redir->type == NODE_REDIRECT_APPEND)
			ft_red_out(ast);
		else 
			ft_red_in(ast);
		io = io->next;
	}
}