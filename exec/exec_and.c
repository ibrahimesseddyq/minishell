/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:49:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/17 21:57:13 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_and(t_astnode *ast, t_lst *env)
{
	exec_cmd_line(ast->binary.left, env);
	if (!ft_exit(1, GET_EXIT_STATUS))
		return (exec_cmd_line(ast->binary.right, env));
}
