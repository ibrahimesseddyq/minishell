/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:08:51 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/06 15:08:58 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

// typedef struct s_arg_node {
//     char *arg;
//     struct s_arg_node *next;
// } t_arg_node;
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
		// printf("[set_command_props] [if] i entered here [%s]\n", new_node->arg);
		node->t_cmd.args = new_node;
		*current = new_node;
	}
	else
	{
		// printf("[set_command_props] [else] i entered here [%s]\n",new_node->arg);
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
		node->t_cmd.cmd = strdup(av[0]);
	else
		node->t_cmd.cmd = NULL;
	(1) && (node->t_cmd.args = NULL, current = NULL);
	while (i < ac)
	{
		new_node = (t_arg_node *)gcalloc(sizeof(t_arg_node));
		new_node->arg = strdup(av[i]);
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

	// printf("delimiter 2 [%s], is there a quote [%d]\n", delimiter, there_is_quote(delimiter));
	if (there_is_quote(delimiter))
		expanded_line = line;
	else
		expanded_line = ft_expand_heredoc(line, env);
	if (!expanded_line)
		return (ft_close(&fd), 0);
	write(fd, expanded_line, strlen(expanded_line));
	write(fd, "\n", 1);
	return (1);
}

int	write_heredoc_to_file(char *delimiter, char *filename, t_lst *env)
{
	static int	file_counter;
	int			fd;
	char		*line;
	char		*non_expanded_delimiter;

	signal(SIGINT, ft_handler);
	non_expanded_delimiter = delimiter;
	delimiter = ft_expand_delimiter(delimiter);
		// signal(SIGINT, handle_sig);

	ft_sprintf(filename, "heredoc_file_%d", file_counter++);
	file_counter = 1;
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");

		if (!ttyname(0))
		{
			open(ttyname(2), O_RDWR);
			// close(fd);
			if(g_sig_var)
				return (ft_close(&fd), -1);
			return (0);
		}
		if (!line)
			return (ft_close(&fd), 0);

		if (strcmp(line, delimiter) == 0)
			break ;
		if (!write_expanded_line(non_expanded_delimiter, line, fd, env))
			return (-1);
	}
	return (ft_close(&fd), 0);
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
