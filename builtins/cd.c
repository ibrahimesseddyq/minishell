#include "../minishell.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define NO_EXIT 0
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
		r = (char *)malloc(sizeof(char) * 2);
		if (!r)
			return (-1);
		return (*r = c, *(r + 1) = '\0', *s = r, 0);
	}
	size = ft_strlen(*s);
	r = (char *)malloc(sizeof(char) * (size + 1));
	if (!r)
		return (-1);
	my_string_copy(*s, r);
	r[size - 1] = c;
	r[size] = '\0';
	return (free(*s), *s = r, 0);
}

static int update_pwd(char **old_pwd, int mode, t_lst *env)
{
    char *current_pwd;
    char **arguments;

    arguments = malloc(3 * sizeof(char *));
    if (!arguments)
        return (ft_exit(EXIT_FAILURE, mode), -1);
    arguments[2] = NULL;

    current_pwd = ft_pwd();
    if (!current_pwd)
        return (perror("cd fails to get current working directory"), ft_exit(EXIT_FAILURE, mode), -1);

    set_env(env ,"PWD", current_pwd);
    if (old_pwd)
    {
        set_env(env, "OLDPWD", *old_pwd);
    }
    return (0);
}

static int change_directory(const char *dir, t_lst *env)
{
    char *new_dir = NULL;

    if (!dir)
    {
        if (!get_env(env, "HOME"))
            return (perror("cd HOME environment variable not set"), -1);
        new_dir = ft_strdup(get_env(env, "HOME"));
    }
    else
        new_dir = ft_strdup(dir);
    if (!new_dir)
        return (perror("cd "), -1);
    if (append_char_to_string(&new_dir, '/') == -1)
        return (perror("cd"), -1);
    if (chdir(new_dir) == -1)
        return (perror("cd"), -1);
    return (0);
}

static int go_to_home_directory(int mode, t_lst *env)
{
    char *home_directory;

    home_directory = ft_strdup(get_env(env, "HOME"));
    if (!home_directory)
    {
        ft_exit(EXIT_FAILURE, mode);
        return -1;
    }

    if (chdir(home_directory) == -1)
    {
        perror("cd");
        return -1;
    }

    return update_pwd(NULL, mode, env);
}

int ft_cd(int argc, char **argv, int mode, t_lst *env)
{
    char *previous_pwd;

    previous_pwd = ft_pwd();
    if (!previous_pwd)
        return (go_to_home_directory(mode, env), perror("cd"), ft_exit(EXIT_FAILURE, mode), 1);
    if (argc > 1)
    {
        if (change_directory(argv[1], env) == -1)
            return (ft_exit(EXIT_FAILURE, mode), -1);
    }
    else if (change_directory(NULL, env) == -1)
        return (ft_exit(EXIT_FAILURE, mode), -1);
    update_pwd(&previous_pwd, mode, env);
    ft_exit(EXIT_SUCCESS, mode);
    return (0);
}
