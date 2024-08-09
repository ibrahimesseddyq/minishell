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
char *expand_tilde(char *path, t_lst *env)
{
    if (path[0] == '~')
    {
        char *home = get_env(env, "HOME");
        if (!home)
            return ft_strdup(path);
        return ft_strjoin(home, path + 1);
    }
    return ft_strdup(path);
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

// static int change_directory(char *dir, t_lst *env)
// {
//     char *new_dir = NULL;
//     if (!dir)
//     {
//         if (!get_env(env, "HOME"))
//             return (perror("cd: HOME environment variable not set"), -1);
//         new_dir = ft_strdup(get_env(env, "HOME"));
//     }
//     else
//         new_dir = ft_strdup(dir);
    
//     if (!new_dir)
//         return (perror("cd"), -1);
    
//     if (chdir(new_dir) == -1)
//     {
//         free(new_dir);
//         return (perror("cd"), -1);
//     }
    
//     free(new_dir);
//     return (0);
// }

int ft_cd(int argc, char **argv, int mode, t_lst *env)
{
    char *dir = NULL;
    char *expanded_dir = NULL;
    char *previous_pwd = ft_pwd();

    // printf("argc %d\n",argc);
    if (argc > 2)
    {
        printf("minishell: cd: too many arguments\n");
        ft_exit(EXIT_FAILURE, SET_EXIT_STATUS);
        return (EXIT_FAILURE);
    }
    if (!previous_pwd)
        return (perror("cd"), ft_exit(EXIT_FAILURE, mode), 1);

    if (argc > 1 && strcmp(argv[1], "-") == 0)
    {
        dir = get_env(env, "OLDPWD");
        if (!dir)
            return (fprintf(stderr, "minishell: cd: OLDPWD not set\n"), free(previous_pwd), ft_exit(EXIT_FAILURE, mode), 1);
    }
    else if (argc > 1)
    {
        dir = argv[1];
    }
    else
    {
        dir = get_env(env, "HOME");
        if (!dir)
            return (fprintf(stderr, "minishell: cd: HOME not set\n"), free(previous_pwd), ft_exit(EXIT_FAILURE, mode), 1);
    }

    expanded_dir = expand_tilde(dir, env);
    if (!expanded_dir)
        return (perror("cd"), free(previous_pwd), ft_exit(EXIT_FAILURE, mode), 1);

    if (chdir(expanded_dir) == -1)
    {
        perror("cd");
        free(expanded_dir);
        free(previous_pwd);
        return (ft_exit(EXIT_FAILURE, mode), 1);
    }

    if (update_pwd(&previous_pwd, mode, env) == -1)
        return (free(previous_pwd), ft_exit(EXIT_FAILURE, mode), 1);

    ft_exit(EXIT_SUCCESS, mode);
    return (0);
}
