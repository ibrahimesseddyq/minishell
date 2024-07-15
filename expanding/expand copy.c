#include "../minishell.h"
#include "../frontend/frontend.h"

int find_keyx(char *key, char *env)
{
	int i;

	i = 0;
	while(key[i] && key[i] == env[i])
	{
        if (key[i + 1] == '=' && !env[i + 1])
			return (1); 
		i++;
	}
	return (0);
}

char	*expandxx(char **key, char *the_env)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	if (!the_env || !the_env[0])
		return (NULL);
	while (key[i] && key)
	{
		k = find_keyx(key[i], the_env);
		if (k == 1)
			return (ft_strchr(key[i], '=') + 1);
		i++;
	}
	return (NULL);
}
