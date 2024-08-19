/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armanov <armanov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:00:33 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/08/15 18:42:34 by armanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	// if ((count > 0 && size > SIZE_MAX / count) || (count < 0 && size < 0))
	// {
	// 	return (NULL);
	// }
	tmp = (void *)malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, (count * size));
	return (tmp);
}
