/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:42:56 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/09 19:35:09 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static int	handle_tty_input(int fd)
{
	open(ttyname(2), O_RDWR);
	if (g_sig_var)
		return (ft_close(&fd), -1);
	return (0);
}

static int	process_line(char *line, t_heredoc_data *data)
{
	if (!line)
		return (0);
	// printf("line [%s] del [%s]\n", line, data->delimiter);
	if (strcmp(line, data->delimiter) == 0)
		return (0);
	if (!write_expanded_line(data->non_expanded_delimiter,
			line, data->fd, data->env))
		return (-1);
	return (2);
}

static int	read_and_process_lines(t_heredoc_data *data)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline("> ");
		if (!ttyname(0))
			return (handle_tty_input(data->fd));
		result = process_line(line, data);
		if (result != 2)
			return (result);
	}
	return (0);
}

int	write_heredoc_to_file(char *delimiter, char *filename, t_lst *env)
{
	static int		file_counter;
	t_heredoc_data	data;
	int				res;

	signal(SIGINT, ft_handler);
	data.non_expanded_delimiter = delimiter;
	data.delimiter = ft_expand_delimiter(delimiter);
	ft_sprintf(filename, "heredoc_file_%d", file_counter++);
	file_counter = 1;
	data.fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data.fd < 0)
		return (-1);
	data.env = env;
	res = read_and_process_lines(&data);
	close(data.fd);
	// printf("res [%d]\n", res);
	return (res);
}
