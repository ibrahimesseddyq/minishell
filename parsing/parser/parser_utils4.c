/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:42:56 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/29 08:13:50 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static int	handle_tty_input(int fd, t_heredoc_data *data)
{
	int	fd2;

	fd2 = open(ttyname(2), O_RDWR);
	if (g_sig_var)
	{
		return (unlink(data->filename), ft_close(&data->fd_rd), ft_close(&fd), -1);
	}
	return (0);
}

static int	process_line(char *line, t_heredoc_data *data)
{
	if (!line)
		return (0);
	if (ft_strcmp(line, data->delimiter) == 0)
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
			return (free(line), handle_tty_input(data->fd, data));
		result = process_line(line, data);
		if (result != 2)
			return (free(line), result);
		free(line);
	}
	return (0);
}

int	write_heredoc_to_file(char *delimiter,
	char *filename, t_lst *env, int *fd_rd)
{
	static int		file_counter;
	t_heredoc_data	data;
	int				res;

	signal(SIGINT, ft_handler);
	data.non_expanded_delimiter = ft_strdup(delimiter);
	data.delimiter = ft_expand_delimiter(ft_strdup(delimiter));
	ft_sprintf(filename, "/tmp/heredoc_file_%d", file_counter);
	data.filename = filename;
	file_counter++;
	data.fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (data.fd < 0)
		return (-1);
	*fd_rd = open(filename, O_RDONLY, 0777);
	add_heredoc_fd_to_list(fd_rd);
	data.fd_rd = *fd_rd;
	if (*fd_rd < 0)
		return (unlink(filename), ft_close(&data.fd), -1);
	unlink(filename);
	data.env = env;
	res = read_and_process_lines(&data);
	ft_close(&data.fd);
	return (res);
}
