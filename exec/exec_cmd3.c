#include "../minishell.h"
#include "../frontend/frontend.h"
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>
#include <glob.h>

char	**split_string(char *str)
{
	int count;
	char *tmp;
	char *token;
	char **result;
	int i;

	count = 0;
	tmp = strdup(str);
	token = strtok(tmp, " ");
	while (token)
	{
		count++;
		token = strtok(NULL, " ");
	}
	result = gcalloc(sizeof(char *) * (count + 1));
	i = 0;
	tmp = strdup(str);
	token = strtok(tmp, " ");
	while (token)
	{
		result[i] = strdup(token);
		i++;
		token = strtok(NULL, " ");
	}
	result[i] = NULL;
	return (result);
}

char	*arg_cmds(char *cmd, t_lst *env)
{
	char	*path;
	char	**path_dirs;
	char	*cmd_path;
	
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.' || is_builtin_command(cmd))
		return ft_strdup(cmd);
	path = get_env(env, "PATH");
	if (!path)
		return (ft_strdup(cmd));

	path_dirs = ft_split(path, ':');
	if (!path_dirs)
		return (ft_strdup(cmd));

	cmd_path = find_command_in_path(cmd, path_dirs);
	if (cmd_path)
		return (cmd_path);
	else
		return (ft_strdup(cmd));
}

int	is_absolute_path(const char *path)
{
	return (path[0] == '/');
}

int	is_relative_path(const char *path)
{
	return (path[0] == '.' && (path[1] == '/' || (path[1] == '.' && path[2] == '/')));
}

const int is_relative_absolute(const char *path)
{
	if (is_absolute_path(path))
		return (1);
	else if (is_relative_path(path))
		return (1);
	else
		return (0);
}