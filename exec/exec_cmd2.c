/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:52:54 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/21 05:05:29 by ibes-sed         ###   ########.fr       */
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

void	handle_exec_error()
{
	if (errno == ENOENT)
		(write(2, "No such file or directory \n", 29), exit(127));
	if (errno == EACCES)
		(write(2, "Permission denied\n", 19), exit(126));
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

t_arg_node	*replace_node_args(t_arg_node *current,
		char **expanded_args, int count)
{
	t_arg_node	*prev;
	t_arg_node	*new_node;
	t_arg_node	*first_new_node;
	int			i;

	first_new_node = NULL;
	new_node = NULL;
	prev = NULL;
	i = 0;
	while (i < count)
	{
		new_node = (t_arg_node *)gcalloc(sizeof(t_arg_node));
		new_node->arg = expanded_args[i];
		new_node->next = NULL;
		if (prev)
			prev->next = new_node;
		else
			first_new_node = new_node;
		prev = new_node;
	}
	if (prev)
		prev->next = current->next;
	return (prev);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
