/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:08:51 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 10:00:41 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_sig_var = 1;
		ft_exit(1, SET_EXIT_STATUS);
	}
}

void	set_command_props(t_arg_node **current
		, t_astnode *node, t_arg_node *new_node)
{
	new_node->next = NULL;
	if (node->t_cmd.args == NULL)
	{
		node->t_cmd.args = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

t_astnode	*create_ast_command(int ac, char **av)
{
	t_astnode	*node;
	t_arg_node	*new_node;
	t_arg_node	*current;
	int			i;

	i = 0;
	node = (t_astnode *)gcalloc(sizeof(t_astnode));
	if (!av || !av[0])
		return (node);
	node->type = NODE_COMMAND;
	if (av && av[0] != NULL)
		node->t_cmd.cmd = ft_strdup(av[0]);
	else
		node->t_cmd.cmd = NULL;
	(1) && (node->t_cmd.args = NULL, current = NULL);
	while (i < ac)
	{
		new_node = (t_arg_node *)gcalloc(sizeof(t_arg_node));
		new_node->arg = ft_strdup(av[i]);
		set_command_props(&current, node, new_node);
		i++;
	}
	(1) && (node->t_cmd.args_size = ac - 1, node->t_cmd.redirections = NULL,
		node->t_cmd.flag_infiles = 0, node->t_cmd.flag_outfiles = 0);
	return (node);
}

int	write_expanded_line(char *delimiter, char *line, int fd, t_lst *env)
{
	char	*expanded_line;

	if (there_is_quote(delimiter))
		expanded_line = line;
	else
		expanded_line = ft_expand_heredoc(line, env);
	if (!expanded_line)
		return (ft_close(&fd), 0);
	write(fd, expanded_line, ft_strlen(expanded_line));
	write(fd, "\n", 1);
	return (1);
}

int	heredoc_delimiter_valid(char *del)
{
	int	quotes_valid;

	quotes_valid = is_valid_quotes(del);
	if (!quotes_valid)
		return (ft_exit(258, SET_EXIT_STATUS),
			write(2, "syntax error in quotes\n", 24), 0);
	return (1);
}
