#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minishell.h"
#include "../frontend/frontend.h"
// Function to get the last exit code (placeholder implementation)
char get_last_exit_code(){
    return '1'; // This should be replaced with the actual last exit code logic
}
char *ft_itoa(int num)
{
    int temp_num = num;
    int len = 1;
    int sign = num < 0 ? -1 : 1;
    if (num < 0) len++; // account for negative sign

    // Calculate the length of the number
    while (temp_num /= 10)
        len++;
    
    char *str = malloc(len + 1); // +1 for null terminator
    if (!str) return NULL;
    
    str[len] = '\0'; // null terminator
    while (len--) {
        str[len] = (num % 10) * sign + '0';
        num /= 10;
    }

    if (sign == -1)
        str[0] = '-';

    return str;
}
// Function to expand variables in the input line
char *ft_expand(char *line)
{
    printf("expand entered\n");
    int is_inside_quotes = 0;
    char current_quote = 0;
    char *start = line;
    int i = 0;
    char *expanded_line = malloc(sizeof(char) * 1024); // Allocate memory for the expanded line
    int expanded_index = 0;

    while (start[i])
    {
        printf("infinite\n");
        if (start[i] == '\'' || start[i] == '\"')
        {
            if (is_inside_quotes == 0) {
                is_inside_quotes = 1;
                current_quote = start[i];
                i++;
                continue;
            } else if (is_inside_quotes == 1 && start[i] == current_quote) {
                is_inside_quotes = 0;
                current_quote = 0;
                i++;
                continue;
            }
        }
        if ((is_inside_quotes == 0 || (is_inside_quotes == 1 && current_quote == '\"')) && start[i] == '$')
        {
            i++;
            if (start[i] == '?')
            {
                expanded_line[expanded_index++] = get_last_exit_code();
                i++;
            } 
            else if (start[i] == '$')
            {
            //   printf("HERE DOESNT GIVE PID\n");
                char *pid_str;
                pid_str = ft_itoa(getpid());
                strcpy(&expanded_line[expanded_index], pid_str);
                expanded_index += strlen(pid_str);
                i++;
            }
            else if (start[i] == ' ' || start[i] == '\0')
            {
                expanded_line[expanded_index++] = '$';
            }
            else
            {
                char varName[256] = {0};
                int j = 0;
                while (start[i] != ' ' && start[i] != '\0' && start[i] != '\'' && start[i] != '\"') {
                    varName[j++] = start[i++];
                }
                varName[j] = '\0';
                char *value = get_env(varName);
                if (value) {
                    strcpy(&expanded_line[expanded_index], value);
                    expanded_index += strlen(value);
                } else {
                    expanded_line[expanded_index++] = '\0';
                    strcpy(&expanded_line[expanded_index], varName);
                    expanded_index += strlen(varName);
                }
            }
        }
        else
        {
            expanded_line[expanded_index++] = start[i];
            i++;
        }
    }
    expanded_line[expanded_index] = '\0';
    return expanded_line;
}
// int main()
// {
//     char *line = "$$";
//     char *expanded_line = ft_expand(line);
//     printf("Expanded line: %s\n", expanded_line);
//     free(expanded_line);
//     return 0;
// }   