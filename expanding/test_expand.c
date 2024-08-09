#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minishell.h"
#include "../frontend/frontend.h"
#include <stdlib.h>
#include <string.h>

// Assuming these are defined elsewhere

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

char *ft_expand(char *line, t_lst *env)
{
    int is_inside_quotes = 0;
    char current_quote = 0;
    char *start = line;
    int i = 0;
    char *expanded_line = malloc(sizeof(char) * 1024); // Allocate memory for the expanded line
    int expanded_index = 0;

    while (start[i])
    {
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
                int exit_status = ft_exit(0, GET_EXIT_STATUS);
                // printf("exit status %d\n", exit_status);
                char *exit_status_str = ft_itoa(exit_status);
                strcpy(&expanded_line[expanded_index], exit_status_str);
                expanded_index += strlen(exit_status_str);
                free(exit_status_str);
                i++;
            }
            else if (start[i] == ' ' || start[i] == '\0' || start[i] == '\'' || start[i] == '\"')
            {
                expanded_line[expanded_index++] = '$';
            }
            else
            {
                char varName[256] = {0};
                int j = 0;
                while (start[i] && start[i] != ' ' && start[i] != '\'' && start[i] != '\"' && start[i] != '/' && start[i] != '$') {
                    varName[j++] = start[i++];
                }
                varName[j] = '\0';
                char *value = get_env(env, varName);
                if (value) {
                    strcpy(&expanded_line[expanded_index], value);
                    expanded_index += strlen(value);
                } else {
                    expanded_line[expanded_index++] = '$';
                    strcpy(&expanded_line[expanded_index], varName);
                    expanded_index += strlen(varName);
                }
            }
        }
        else
        {
            expanded_line[expanded_index++] = start[i++];
        }
    }
    expanded_line[expanded_index] = '\0';
    return expanded_line;
}