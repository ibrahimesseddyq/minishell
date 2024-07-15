#include "../minishell.h"
#include "../frontend/frontend.h"

char	*get_env(t_lst *env, char *the_env)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	if (!the_env || !the_env[0])
		return (NULL);
	while (env->next)
	{	
		if (ft_strncmp(env->key,the_env, ft_strlen(the_env)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
