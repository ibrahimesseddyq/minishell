/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:00:05 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/17 18:07:32 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

t_astnode	*parse_pipe(t_tklist *tokens, t_lst *lst)
{
	t_astnode	*node1;
	t_token		*token;
	t_astnode	*node2;

	node1 = parse_cmd(tokens, lst);
	if (!node1)
		return (NULL);
	token = peek_token(tokens);
	while (token && token->type == TK_PIPE)
	{
		next_token(tokens);
		node2 = parse_cmd(tokens, lst);
		if (!node2)
			return (NULL);
		node1 = create_binary_node(NODE_PIPE, node1, node2);
		token = peek_token(tokens);
	}
	return (node1);
}

t_astnode	*parse_and_or(t_tklist *tokens
		, t_astnode *left, t_token *token, t_lst *lst)
{
	t_astnode	*node;
	t_astnode	*right;

	node = NULL;
	right = NULL;
	if (token->type == TK_AND)
	{
		right = parse_pipe(tokens, lst);
		if (!right)
			return (NULL);
		node = create_binary_node(NODE_LOGICAL_AND, left, right);
	}
	else if (token->type == TK_OR)
	{
		right = parse_pipe(tokens, lst);
		if (!right)
			return (NULL);
		node = create_binary_node(NODE_LOGICAL_OR, left, right);
	}
	return (node);
}

t_astnode	*parse_command_line(t_tklist *tokens, t_lst *lst)
{
	t_astnode	*node;
	t_astnode	*right;
	t_token		*token;

	node = parse_block(tokens, lst);
	if (!node)
		return (NULL);
	token = peek_token(tokens);
	while (token && (token->type == TK_AND || token->type == TK_OR))
	{
		token = next_token(tokens);
		right = parse_command_line(tokens, lst);
		if (!right)
			return (NULL);
		if (token->type == TK_AND)
			node = create_binary_node(NODE_LOGICAL_AND, node, right);
		else if (token->type == TK_OR)
			node = create_binary_node(NODE_LOGICAL_OR, node, right);
		token = peek_token(tokens);
	}
	return (node);
}

t_astnode	*parse_block(t_tklist *tokens, t_lst *lst)
{
	t_token		*token;
	t_astnode	*node;
	t_astnode	*block_node;

	token = peek_token(tokens);
	if (token && token->type == TK_LPR)
	{
		next_token(tokens);
		node = parse_command_line(tokens, lst);
		if (!node)
			return (NULL);
		token = next_token(tokens);
		if (!token || token->type != TK_RPR)
			return (NULL);
		block_node = create_block_node(node);
		if (!block_node)
			return (NULL);
		return (block_node);
	}
	else
		return (parse_pipe(tokens, lst));
}
