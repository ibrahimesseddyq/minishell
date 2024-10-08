/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:24:20 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/08 14:56:47 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**remove_empty_strings(char **arr, int size, int *new_size)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	j = 0;
	new_arr = gcalloc(size * sizeof(char *));
	while (arr[i])
	{
		if (arr[i][0])
		{
			new_arr[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	*new_size = j + 1;
	new_arr = ft_realloc
		(new_arr, j * sizeof(char *), (*new_size) * sizeof(char *));
	new_arr[*new_size - 1] = NULL;
	return (arr);
}

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

	i = 0;
	empty_str = get_empty_str();
	while (i <= size && args[i])
	{
		str = args[i];
		if (!ft_strcmp(str, empty_str))
		{
			args[i] = ft_strdup("");
			i++;
			continue ;
		}
		j = 0;
		while (str[j])
		{
			if (str[j] == *get_splitted_char(2))
				str[j] = ' ';
			j++;
		}
		i++;
	}
	return (args);
}

int	special_cases(char *cmd)
{
	struct stat	sb;

	stat(cmd, &sb);
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
	else if (((cmd[ft_strlen(cmd) - 1] == '/' && S_ISDIR(sb.st_mode))
			|| S_ISDIR(sb.st_mode)) && !is_builtin_command(cmd))
	{
		write(2, "Is a directory \n", 16);
		ft_exit(126, SET_EXIT_STATUS);
		return (1);
	}
	return (0);
}
