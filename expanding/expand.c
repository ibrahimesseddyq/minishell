#include "../minishell.h"
#include "../frontend/frontend.h"

int find_key(char *key, char *env, int k)
{
	int i;

	i = 0;
	while(key[i])
	{
		if (key[i] == env[i])
		{	
            if (key[i + 1] == '=' && !env[i + 1])
                break ;
            i++;
        }else
			return (0);
	}
	return (k);
}

char	*expand(char **key, char *the_env)
{
	int	i;

	i = 0;
	while (key[i] && key)
	{
		if (find_key(key[i], the_env, i) > 0)
			return (ft_strchr(key[i], '=') + 1);
		i++;
	}
	return (NULL);
}
