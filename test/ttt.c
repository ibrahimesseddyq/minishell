#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int find_key(char *key, char *env)
// { 
//     int i;

//     i = 0;
//     while(key[i] && key[i] != '=')
//     {
//         if (key[i] == env[i])
//             i++;
//         else 
//             return (0);
//     }
//     return (1);
// }

// int find_key(char *key, char *env)
// {
// 	int i;

// 	i = 0;
// 	while(key[i])
// 	{
// 		if (key[i] == env[i])
// 		{
//             if (key[i + 1] == '=' && !env[i + 1])
//                 break ;
//             i++;
//         }
// 		else
// 			return (0);
// 	}
// 	return (1);
// }

// char	*expand(char *key, char *the_env)
// {
// 	if (find_key(key, the_env) != 0)
// 		return (strchr(key, '=') + 1);
// 	return (NULL);
// }

void	parcing(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			printf("this is : ' \n");
		if (word[i] == '"')
			printf("this is : \" \n");
		i++;
	}
}

int find_key(char *key, char *env)
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

char	*expand(char **key, char *the_env)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	if (!the_env || !the_env[0])
		return (NULL);
	while (key[i] && key)
	{	
		k =  find_key(key[i], the_env);
		if (k == 1)
			return (strchr(key[i], '=') + 1);
		i++;
	}
	return (NULL);
}

int main(int ac, char **av, char *envp[]) {
	(void)ac;
	// (void)av;

	// char **env;
	// int	i;
	// int	size;
	// size = 0;
	// while (envp[size])
	// 	size++;
	// env = malloc(size * sizeof(char *));
    // // char *key = "PWD=/Users/ynachat/Desktop/test_brahim";
    // // char env[20] = "PWDfbdbgb";

	// i = 0;
	// while (envp[i])
	// {
	// 	env[i] = strdup(envp[i]);
	// 	i++;
	// }
	// i = 0;
	// env[size] = NULL;
   	// char *result = expand(env, av[1]);
    // if (result)
    //     printf("%s\n", result);
    // else
    //     printf("Key not found\n");
    parcing(av[1]);
	// printf("%s\n", expand(key,env));
}
