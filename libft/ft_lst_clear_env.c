/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:55:48 by ynachat           #+#    #+#             */
/*   Updated: 2024/07/14 22:38:01 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_clear_env(t_lst **lst)
{
	t_lst	*l;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		l = (*lst)->next;
		free(*lst);
		*lst = l;
	}
	*lst = NULL;
}