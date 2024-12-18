/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:52:54 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/28 08:55:54 by ibes-sed         ###   ########.fr       */
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
		if (env->key && env->key[0])
		{
			var = ft_strjoin(ft_strjoin(env->key, "="), env->value);
			envp[i++] = var;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	handle_exec_error(void)
{
	if (errno == EACCES)
	{
		(write(2, "Permission denied\n", 19), gc_free_all(), exit(126));
	}
	else if (errno == ENOTDIR)
		(write(2, "Not a directory\n", 17), gc_free_all(), exit(126));
	else if (errno == ENOEXEC)
		(write(2, "Exec Error\n", 12), gc_free_all(), exit(2));
	else if (errno == E2BIG)
		(write(2, "Argument list too long\n", 24), gc_free_all(), exit(126));
	else if (errno == ENOMEM)
		(write(2, "Out of memory\n", 15), gc_free_all(), exit(126));
	else if (errno == ETXTBSY)
		(write(2, "Text file busy\n", 16), gc_free_all(), exit(126));
	else if (errno == EISDIR)
		(write(2, "is a directory\n", 16), gc_free_all(), exit(126));
	gc_free_all();
	exit(0);
}
