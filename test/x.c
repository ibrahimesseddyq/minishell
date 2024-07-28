# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

void find_key(char *env)
{
	int i;
	i = 0;
	char *tmp;
	tmp = NULL;
	while (env[i] && env[i] != '=')
		i++;
	// if (env[i] == '=')
    printf("her--> %c\n", env[i]);
	// tmp = strdup(substr(env, 0, i));
	// return (tmp);
}

int main() {
    find_key("hiiiihhd=");
    // printf("%s\n", );

    return 0;
}
