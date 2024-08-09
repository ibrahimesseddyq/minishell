/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/03 10:42:53 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_and(t_astnode *ast, t_st *st, t_lst *env)
{
	exec_cmd_line(ast->binary.left, st, env);
	if (st->st == 0)
		exec_cmd_line(ast->binary.right, st, env);
}
