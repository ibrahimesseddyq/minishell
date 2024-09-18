#include "../minishell.h"

#define EXIT_FAIL 2
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

int ft_cd(int argc, char **argv, int mode, t_lst *env)
{
    char *dir = NULL;
    char *expanded_dir = NULL;
    char *previous_pwd = ft_pwd();
    char *pwd = ft_strdup(ft_pwd());
    if (!previous_pwd || !pwd)
    {
        perror("cd");
        ft_exit(1 , mode);
        return 1;
    }
    set_env(env, "OLDPWD", previous_pwd, 1);


    if (argc == 1)
    {
        dir = get_env(env, "HOME");
        // printf("is set %d\n",get_env_isset(env,"HOME"));
        if (!dir || !dir[0] && !get_env_isset(env,"HOME"))
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            ft_exit(1 , mode);
            return 1;
        }
        else if(!dir || !dir[0] && get_env_isset(env,"HOME"))
        {
            ft_exit(0, SET_EXIT_STATUS);
            return (0);
        }
    }
    else if (strcmp(argv[1], "-") == 0)
    {
        dir = get_env(env, "OLDPWD");
        if (!dir || !*dir)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            ft_exit(1 , mode);
            return 1;
        }
    }
    else
    {
        dir = argv[1];
    }

    if (strcmp(dir, ".") == 0)
    {
        ft_exit(EXIT_SUCCESS, mode);
        return 0;
    }
    // printf("[cd] dir %s\n",dir);

    expanded_dir = expand_tilde(dir, env);
    if (!expanded_dir)
    {

        perror("cd");
        ft_exit(EXIT_FAIL, mode);
        return 1;
    }
    if (chdir(expanded_dir) == -1)
    {
        perror("cd");

        ft_exit(EXIT_FAILURE, mode);
        return 1;
    }

    char *new_pwd = ft_pwd();

    if (!new_pwd)
    {
        perror("cd: failed to get new working directory");
        ft_exit(EXIT_FAIL, mode);
        return 1;
    }
    set_env(env, "PWD", new_pwd, 1);


    ft_exit(EXIT_SUCCESS, mode);
    return 0;
}