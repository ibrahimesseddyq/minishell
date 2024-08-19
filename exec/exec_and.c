/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/18 06:58:44 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_and(t_astnode *ast, t_lst *env)
{
	exec_cmd_line(ast->binary.left, env);
	if (ft_exit(4,GET_EXIT_STATUS) == 0)
		exec_cmd_line(ast->binary.right, env);
}
