/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:01:09 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/25 22:01:12 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_cmd_line(t_astnode *ast, t_st *st)
{
	if (ast->type == 0)
	{
		// printf("dkhelt\n");
		exec_cmd(ast, st);
	}
	else if (ast->type == 1)
		exec_pip(ast);
	else if (ast->type == 5)
		exec_and(ast, st);
	else if (ast->type == 6)
		exec_or(ast, st);

}
