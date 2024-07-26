/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:39 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/25 22:00:40 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_or(t_astnode *ast, t_st *st)
{
	exec_cmd_line(ast->binary.left, st);
	if (st->st != 0)
		exec_cmd_line(ast->binary.right, st);
}
