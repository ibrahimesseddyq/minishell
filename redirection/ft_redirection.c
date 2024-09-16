/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:21:45 by ynachat           #+#    #+#             */
/*   Updated: 2024/09/16 19:28:35 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../frontend/frontend.h"

int *get_last_redirs(t_astnode *ast)
{
    int last_in = -1;
    int last_out = -1;
    int i = 0;
    int *last_arr = gcalloc(sizeof(int) * 2);
    t_redir_list *current = ast->t_cmd.redirections;

    while (current)
    {
        if (current->redir && (current->redir->type == NODE_REDIRECT_OUT || current->redir->type == NODE_REDIRECT_APPEND))
            last_out = i;
        else
            last_in = i;

        i++;
        current = current->next;
    }

    last_arr[0] = last_in;
    last_arr[1] = last_out;
    return last_arr;
}

int	ft_redirection(t_astnode *ast, t_lst *env, int command_exist)
{
	int	fd;

	int last_arr[2];
	int i;

	last_arr[0] = get_last_redirs(ast)[0];
	last_arr[1] = get_last_redirs(ast)[1];
	i = 0;

	if (last_arr[0] == 0 && last_arr[1] == 0)
		return (1);
	while (ast->t_cmd.redirections)
	{
		if (ast->t_cmd.redirections->redir && (ast->t_cmd.redirections->redir->type == NODE_REDIRECT_OUT || ast->t_cmd.redirections->redir->type == NODE_REDIRECT_APPEND))
		{
			fd = ft_red_out(ast, env, last_arr[1] == i, command_exist);
			if (fd == -2)
				return (-2);
				printf(" fd [%d]\n", fd);

		}
		else
		{
			fd = ft_red_in(ast, env, last_arr[0] == i, command_exist);
			if (fd == -2)
				return (-2);
		}
		i++;
		ast->t_cmd.redirections = ast->t_cmd.redirections->next;
	}
	// printf("end redir\n");
	return (fd);
}