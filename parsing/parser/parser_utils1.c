/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:52:42 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/20 15:47:17 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

t_astnode	*create_binary_node(t_node_type type
		, t_astnode *left, t_astnode *right)
{
	t_astnode	*node;

	node = (t_astnode *)gcalloc(sizeof(t_astnode));
	node->type = type;
	node->t_binary.left = left;
	node->t_binary.right = right;
	return (node);
}

t_astnode	*create_redirect_node(t_node_type type
		, t_astnode *child, char *filename)
{
	t_astnode	*node;

	node = (t_astnode *)gcalloc(sizeof(t_astnode));
	node->type = type;
	node->t_redirect.child = child;
	node->t_redirect.filename = ft_strdup(filename);
	return (node);
}

t_astnode	*create_block_node(t_astnode *child)
{
	t_astnode	*node;

	node = (t_astnode *)gcalloc(sizeof(t_astnode));
	node->type = NODE_BLOCK;
	node->t_block.child = child;
	return (node);
}

int	there_is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

bool	is_valid_quotes(const char *str)
{
	int		i;
	bool	single_open;
	bool	double_open;

	i = 0;
	single_open = false;
	double_open = false;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (str[i] == '"' && !single_open)
			double_open = !double_open;
		i++;
	}
	return (!single_open && !double_open);
}
