/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:00:39 by ynachat           #+#    #+#             */
/*   Updated: 2024/08/09 13:45:40 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"
#include "../frontend/frontend.h"

void exec_or(t_astnode *ast, t_st *st, t_lst *env)
{
	exec_cmd_line(ast->binary.left, st, env);
	if (st->st != 0)
		exec_cmd_line(ast->binary.right, st, env);
}

// int test_permission(char *str)
// {
//     t_stat info;

//     stat(str, &info)
    
//     if(access(str, F_OK) == -1)
//     {

//         return (-1);
//     }
//     else if(access(str, X_OK) == -1)
//         return (-2);
//     return (0);
// }