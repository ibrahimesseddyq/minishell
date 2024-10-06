/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:36:01 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 22:00:30 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char			*new;
	char			*temp;
	unsigned int	i;

	i = 0;
	if (ptr == NULL)
		return (ptr = gcalloc(new_size), ptr);
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
		return (NULL);
	new = gcalloc(new_size);
	if (new == NULL)
		return (NULL);
	if (new_size < old_size)
		old_size = new_size;
	temp = ptr;
	while (i < old_size)
	{
		*(new + i) = *(temp + i);
		i++;
	}
	return (new);
}
