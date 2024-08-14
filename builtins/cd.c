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
		*r = c;
		*(r + 1) = '\0';
		*s = r;
		return (0);
	}
	size = ft_strlen(*s);
	r = (char *)malloc(sizeof(char) * (size + 2));
	if (!r)
		return (-1);
	my_string_copy(*s, r);
	r[size] = c;
	r[size + 1] = '\0';
	free(*s);
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
        free(previous_pwd);
        free(pwd);
        ft_exit(EXIT_FAILURE, mode);
        return 1;
    }
    printf("[cd] 1 - previous_pwd is %s\ncalls set_env\n",previous_pwd);


    if (argc > 2)
    {
        fprintf(stderr, "minishell: cd: too many arguments\n");
        free(previous_pwd);
        free(pwd);
        ft_exit(EXIT_FAILURE, mode);
        return 1;
    }

    if (argc == 1)
    {
        dir = get_env(env, "HOME");
        if (!dir)
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            free(previous_pwd);
            free(pwd);
            ft_exit(EXIT_FAILURE, mode);
            return 1;
        }
    }
    else if (strcmp(argv[1], "-") == 0)
    {
        dir = get_env(env, "OLDPWD");

        if (!dir || !*dir)
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            free(previous_pwd);
            free(pwd);
            ft_exit(EXIT_FAILURE, mode);
            return 1;
        }
    }
    else
    {
        printf("[cd] 3 - set DIR %s\n", argv[1]);

        dir = argv[1];
    }
    set_env(env, "OLDPWD", previous_pwd);

    if (strcmp(dir, ".") == 0)
    {
        free(previous_pwd);
        free(pwd);
        ft_exit(EXIT_SUCCESS, mode);
        return 0;
    }
    printf("[cd] 4 - before expand %s\n", dir);

    expanded_dir = expand_tilde(dir, env);
    printf("[cd] 5 - after expand %s\n", expanded_dir);

    if (!expanded_dir)
    {
        free(previous_pwd);
        free(pwd);
        perror("cd");
        ft_exit(EXIT_FAILURE, mode);
        return 1;
    }

    if (chdir(expanded_dir) == -1)
    {
        perror("cd");
        free(expanded_dir);
        free(previous_pwd);
        free(pwd);
        ft_exit(EXIT_FAILURE, mode);
        return 1;
    }

    free(expanded_dir);

    char *new_pwd = ft_pwd();
    printf("[cd] 6 - new pwd %s\n", new_pwd);

    if (!new_pwd)
    {
        perror("cd: failed to get new working directory");
        free(previous_pwd);
        free(pwd);
        ft_exit(EXIT_FAILURE, mode);
        return 1;
    }
    t_lst *env_tmp;
    env_tmp=env;
	while (env_tmp)
	{

		if (ft_strcmp(env_tmp->key, "OLDPWD") == 0)
		{
            printf("[cd] 2 - found OLDPWD %s\n", env_tmp->value);
		}
		env_tmp = env_tmp->next;
	}
    set_env(env, "PWD", new_pwd);

    free(previous_pwd);
    free(pwd);
    free(new_pwd);

    ft_exit(EXIT_SUCCESS, mode);
    return 0;
}