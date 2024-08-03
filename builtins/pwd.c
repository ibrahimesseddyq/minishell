#include "./../minishell.h"

// int ft_pwd(t_lst *env)
// {
//     char *pwd = get_env(env, "PWD");
//     if (!pwd)
//     {
//         perror("minishell");
//         return 0;
//     }
//     printf("%s\n", pwd);
//     return 1;
// }

// int	ft_pwd(int mode, t_lst *env, char **storage)
// {
// 	char	*dir;

//     (void)env;
// 	dir = (char *)malloc(sizeof(char) * MNSH_PATH_MAX);
// 	if (!dir)
// 		return (ft_exit(EXIT_FAILURE, mode));
// 	if (!getcwd(dir, MNSH_PATH_MAX * sizeof(char)))
// 		return (ft_exit(EXIT_FAILURE, mode));
//     *storage = dir;
// 	return (ft_exit(EXIT_SUCCESS, mode));
// }

char	*ft_pwd(void)
{
	char	*dir;

	dir = (char *)malloc(sizeof(char) * MNSH_PATH_MAX);
	if (!dir)
		return (NULL);
	if (!getcwd(dir, MNSH_PATH_MAX * sizeof(char)))
		return (NULL);
	return (dir);
}
