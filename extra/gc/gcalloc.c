/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:17:33 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/23 03:49:25 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

t_allocation	**get_gc_list(void)
{
	static t_allocation	*gc_list;

	return (&gc_list);
}

int	*how_many_allocated(void)
{
	static int	alloc;

	return (&alloc);
}

void	*gcalloc(size_t size)
{
	t_allocation	**list_ptr;
	t_allocation	*new_node;
	int				*allocated;
	void			*alloc;

	allocated = how_many_allocated();
	alloc = malloc(size);
	if (alloc == NULL)
	{
		gc_free_all();
		exit(1);
	}
	ft_memset(alloc, 0, size);
	new_node = malloc(sizeof(t_allocation));
	list_ptr = get_gc_list();
	if (new_node == NULL)
		return (free(alloc), NULL);
	(*allocated)++;
	new_node->address = alloc;
	new_node->freed = 0;
	new_node->next = *list_ptr;
	*list_ptr = new_node;
	return (alloc);
}

void	gc_free(void *ptr)
{
	t_allocation	**list_ptr;
	t_allocation	*current;
	t_allocation	*prev;

	(1) && (list_ptr = get_gc_list(), current = *list_ptr, prev = NULL);
	while (current != NULL)
	{
		if (current->address == ptr)
		{
			if (!current->freed)
			{
				free(current->address);
				current->freed = 1;
			}
			if (prev == NULL)
				*list_ptr = current->next;
			else
				prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_all(void)
{
	t_allocation	**list_ptr;
	t_allocation	*current;
	t_allocation	*next;
	int				freed;

	list_ptr = get_gc_list();
	current = *list_ptr;
	freed = 0;
	while (current != NULL)
	{
		next = current->next;
		if (!current->freed)
		{
			free(current->address);
			current->freed = 1;
		}
		free(current);
		freed++;
		current = next;
	}
	*list_ptr = NULL;
}
