/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:04:04 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/18 19:01:37 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handle_pwd_error(t_lst *env)
{
	char	*home;

	home = get_env(env, "HOME");
	set_env(env, "PWD", home, 1);
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (ft_exit(1, SET_EXIT_STATUS), 1);
	}
	if (chdir(home) == -1)
		return (perror("cd"), ft_exit(1, SET_EXIT_STATUS), 1);
	write(2, "minishell: cd: directory reset to HOME\n", 39);
	return (0);
}

static char	*ft_get_directory(int argc, char **argv, t_lst *env)
{
	char	*dir;

	if (argc == 1 || !argv[1][0])
	{
		dir = get_env(env, "HOME");
		if ((!dir || !dir[0]) && !get_env_isset(env, "HOME"))
			return (write(2, "minishell: cd: HOME not set\n", 28), NULL);
		return (ft_strdup(get_env(env, "HOME")));
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		dir = get_env(env, "OLDPWD");
		if (!dir || !*dir)
			return (write(2, "minishell: cd: OLDPWD not set\n", 30), NULL);
		return (ft_strdup(dir));
	}
	return (ft_strdup(argv[1]));
}

static int	ft_change_directory(char *expanded_dir, t_lst *env, char *pwd)
{
	char	*new_pwd;

	if (chdir(expanded_dir) == -1)
		return (perror("cd"), ft_exit(1, SET_EXIT_STATUS), 1);
	set_env(env, "OLDPWD", pwd, 1);
	new_pwd = ft_pwd(env);
	if (!new_pwd)
	{
		write(2, "cd: failed to get new working directory\n", 40);
		return (ft_exit(1, SET_EXIT_STATUS), 1);
	}
	set_env(env, "PWD", new_pwd, 1);
	return (ft_exit(0, SET_EXIT_STATUS), 0);
}

int	ft_cd(int argc, char **argv, t_lst *env)
{
	char	*pwd;
	char	*dir;
	char	*expanded_dir;

	pwd = ft_strdup(ft_pwd(env));
	if (!pwd)
	{
		if (ft_handle_pwd_error(env))
			return (1);
		pwd = ft_strdup(get_env(env, "HOME"));
		if (!pwd)
			return (perror("cd"), ft_exit(1, SET_EXIT_STATUS), 1);
	}
	dir = ft_get_directory(argc, argv, env);
	if (!dir)
		return (ft_exit(1, SET_EXIT_STATUS), 1);
	if (ft_strcmp(dir, ".") == 0)
		return (ft_exit(0, SET_EXIT_STATUS), 0);
	expanded_dir = ft_expand_tilde(dir, env);
	if (!expanded_dir)
		return (perror("cd"), ft_exit(1, SET_EXIT_STATUS), 1);
	return (ft_change_directory(expanded_dir, env, pwd));
}
