/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:52:54 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/07 14:35:33 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_env_vars(t_lst *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**build_envp(t_lst *env)
{
	char	**envp;
	int		size;
	int		i;
	char	*var;

	size = count_env_vars(env);
	envp = gcalloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		var = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		envp[i++] = var;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	handle_exec_error(void)
{
	if (errno == ENOENT)
		(write(2, "No such file or directory \n", 29), exit(127));
	if (errno == EACCES)
		(write(2, "Permission denied 1\n", 19), exit(126));
	else if (errno == ENOTDIR)
		(write(2, "Not a directory\n", 17), exit(126));
	else if (errno == ENOEXEC)
		(write(2, "Exec format error \n", 20), exit(126));
	else if (errno == E2BIG)
		(write(2, "Argument list too long\n", 24), exit(126));
	else if (errno == ENOMEM)
		(write(2, "Out of memory\n", 15), exit(126));
	else if (errno == ETXTBSY)
		(write(2, "Text file busy\n", 16), exit(126));
	else if (errno == EISDIR)
		(write(2, "is a directory\n", 16), exit(126));
	exit(0);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
