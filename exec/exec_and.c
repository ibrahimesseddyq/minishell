/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/14 23:49:49 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_and(t_astnode *ast, t_st *st)
{
	exec_cmd_line(ast->binary.left, st);
	// printf("[%d]\n", st->st);
	if (st->st == 0)
		exec_cmd_line(ast->binary.right, st);
}
