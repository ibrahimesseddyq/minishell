/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:04:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/09/22 01:49:31 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	my_string_copy(char *from, char *to)
{
	int	i;

	i = -1;
	while (from[++i])
		to[i] = from[i];
	to[i] = '\0';
}

int	append_char_to_string(char **s, char c)
{
	char	*r;
	int		size;

	if (!(*s))
	{
		r = (char *)gcalloc(sizeof(char) * 2);
		if (!r)
			return (-1);
		*r = c;
		*(r + 1) = '\0';
		*s = r;
		return (0);
	}
	size = ft_strlen(*s);
	r = (char *)gcalloc(sizeof(char) * (size + 2));
	if (!r)
		return (-1);
	my_string_copy(*s, r);
	r[size] = c;
	r[size + 1] = '\0';
	*s = r;
	return (0);
}

char	*expand_tilde(char *path, t_lst *env)
{
	char	*home;

	if (path[0] == '~')
	{
		home = get_env(env, "HOME");
		if (!home)
			return (ft_strdup(path));
		return (ft_strjoin(home, path + 1));
	}
	return (ft_strdup(path));
}
	//inside argc ==1 : else if (!dir || !dir[0] && get_env_isset(env, "HOME"))
	// 	return (ft_exit(0, SET_EXIT_STATUS), 0);
int	ft_cd(int argc, char **argv, int mode, t_lst *env)
{
	char	*dir;
	char	*expanded_dir;
	char	*previous_pwd;
	char	*pwd;
	char	*new_pwd;

	dir = NULL;
	expanded_dir = NULL;
	previous_pwd = get_env(env, "OLDPWD");
	pwd = ft_strdup(ft_pwd());
	if (!previous_pwd || !pwd)
		return (perror("cd"), ft_exit(1, mode), 1);
	// printf("argc [%d]\n", argc);
	if (argc == 1)
	{
		dir = get_env(env, "HOME");
		if ((!dir || !dir[0]) && !get_env_isset(env, "HOME"))
			return (write(2, "minishell: cd: HOME not set\n", 29),
				ft_exit(1, mode), 1);
		dir = ft_strdup("/Users/ibes-sed");
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		dir = get_env(env, "OLDPWD");
		// printf("PWD is [%s] and OLDPWD is [%s]\n", pwd, dir);
		if (!dir || !*dir)
			return (write(2, "minishell: cd: OLDPWD not set\n", 31),
				ft_exit(1, SET_EXIT_STATUS), 1);
	}
	else
		dir = argv[1];
	if (strcmp(dir, ".") == 0)
		return (ft_exit(0, SET_EXIT_STATUS), 0);
	expanded_dir = expand_tilde(dir, env);
	if (!expanded_dir)
		return (perror("cd"), ft_exit(1, SET_EXIT_STATUS), 1);
	if (chdir(expanded_dir) == -1)
		return (perror("cd"), ft_exit(1, SET_EXIT_STATUS), 1);
	set_env(env, "OLDPWD", previous_pwd, 1);
	new_pwd = ft_pwd();
	if (!new_pwd)
		return (write(2, "cd: failed to get new working directory\n", 41),
			ft_exit(1, SET_EXIT_STATUS), 1);
	return (set_env(env, "PWD", new_pwd, 1), ft_exit(0, SET_EXIT_STATUS), 0);
}
