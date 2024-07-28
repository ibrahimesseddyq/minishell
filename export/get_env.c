#include "../minishell.h"
#include "../frontend/frontend.h"

char	*get_env(t_lst *env, char *the_env)
{
	if (!the_env || !the_env[0])
		return (NULL);
	while (env->next)
	{
		if (strcmp(env->key, the_env) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
