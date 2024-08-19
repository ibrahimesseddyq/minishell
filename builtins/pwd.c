#include "./../minishell.h"

char	*ft_pwd(void)
{
	char	*dir;

	dir = (char *)gcalloc(sizeof(char) * MNSH_PATH_MAX);
	if (!dir)
		return (NULL);
	if (!getcwd(dir, MNSH_PATH_MAX * sizeof(char)))
		return (NULL);
	return (dir);
}
