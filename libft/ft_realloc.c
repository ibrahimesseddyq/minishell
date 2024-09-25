/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 04:36:01 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/25 21:38:04 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *temp;
	unsigned int i;

	if (ptr == NULL)
	{
		ptr = gcalloc(new_size);

		if (ptr == NULL)
			return (NULL);

		return (ptr);
	}

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		return (NULL);
	}

	new = gcalloc(new_size);

	if (new == NULL)
		return (NULL);

	old_size = (new_size < old_size) ? new_size : old_size;

	temp = ptr;

	for (i = 0; i < old_size; i++)
	{
		*(new + i) = *(temp + i);
	}

	return (new);
}