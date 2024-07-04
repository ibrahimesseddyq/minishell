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

int find_key(char *key, char *env)
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
        }
		else
			return (0);
	}
	return (1);
}

char	*expand(char *key, char *the_env)
{
	if (find_key(key, the_env) != 0)
		return (strchr(key, '=') + 1);
	return (NULL);
}


int main(int ac, char **av, char *envp[]) {
	(void)ac;
	(void)av;


	char **env;
	int	i;
	int	size;
	size = 0;
	while (envp[size])
		size++;
	env = malloc(size * sizeof(char *));
    // char *key = "PWD=/Users/ynachat/Desktop/test_brahim";
    // char env[20] = "PWDfbdbgb";

	// i = 0;
	// while (envp[i])
	// {
	// 	env[i] = strdup(envp[i]);
	// 	i++;
	// }

    if (find_key(key, env) == 1)
        printf("kin \n");
    else 
        printf("makinch\n");
    
	// printf("%s\n", expand(key,env));
}
