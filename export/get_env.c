#include "../minishell.h"
#include "../frontend/frontend.h"

char	*get_env(t_lst *env, char *the_env)
{
	printf("get_env\n");
	if (!the_env || !the_env[0])
		return (NULL);
		printf("here 1\n");
		printf("start of env loop\n");
	if(!env->next)
		return (printf("env is null\n"),NULL);

	while (env->next)
	{
		if(!env->key || !env->value)
			return (printf("key or value are null\n"),NULL);
		if(env && env->key && env->value)
				printf("key=%s, value=%s\n", env->key, env->value);


		if (strcmp(env->key, the_env) == 0)
			return (env->value);
		env = env->next;
	}
	printf("didnt segv in get_env\n");
	return (NULL);
}
