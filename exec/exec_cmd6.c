/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:20 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 02:18:52 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_empty_str(void)
{
	char	*empty_str;

	empty_str = NULL;
	empty_str = gcalloc(2);
	empty_str[0] = *get_splitted_char(3);
	empty_str[1] = '\0';
	return (empty_str);
}

char	**make_array(char **args, int size)
{
	int		i;
	int		j;
	char	*str;
	char	*empty_str;

	(1) && (i = 0, empty_str = get_empty_str());
	while (i <= size && args[i])
	{
		str = args[i];
		j = 0;
		while (str[j])
		{
			if (str[j] == *get_splitted_char(2))
				str[j] = ' ';
			if (str[j] == *get_splitted_char(4))
				str[j] = '*';
			j++;
		}
		i++;
	}
	return (args);
}

int	slash_exist(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}


int	is_a_special_case(char *cmd,struct stat *sb)
{
	if(!ft_strcmp(cmd, "..") || !ft_strcmp(cmd, ".") || (cmd[ft_strlen(cmd) - 1] == '/' && S_ISDIR(sb->st_mode))
		|| (S_ISDIR(sb->st_mode)
			&& !is_builtin_command(cmd) && slash_exist(cmd)))
		return (1);
}
int	special_cases(char *cmd, t_lst *env, t_astnode *ast)
{
	struct stat	sb;
	int			stdout_backup;

	stat(cmd, &sb);
	if (is_a_special_case(cmd, &sb))
	{
		stdout_backup = ft_redirection(ast, env, 0);
		if (stdout_backup == -2)
			return (-2);
		ft_close(&stdout_backup);
		if (!ft_strcmp(cmd, "."))
		{
			write(2, "filename argument required\n", 28);
			ft_exit(2, SET_EXIT_STATUS);
			return (1);
		}
		else if (!ft_strcmp(cmd, ".."))
		{
			write(2, "Command not found\n", 19);
			ft_exit(127, SET_EXIT_STATUS);
			return (1);
		}
		else if ((cmd[ft_strlen(cmd) - 1] == '/' && S_ISDIR(sb.st_mode))
			|| (S_ISDIR(sb.st_mode)
				&& !is_builtin_command(cmd) && slash_exist(cmd)))
		{
			write(2, "Is a directory \n", 17);
			ft_exit(126, SET_EXIT_STATUS);
			return (1);
		}
	}
	return (0);
}

void	is_directory_error(void)
{
	write(2, "is a directory\n", 16);
	ft_exit(126, SET_EXIT_STATUS);
}
