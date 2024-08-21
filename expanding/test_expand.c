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
    char *str = gcalloc(len + 1); // +1 for null terminator
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
    int expanded_size = 64;
    char *expanded_line = gcalloc(expanded_size);
    if (!expanded_line) return NULL;
    int expanded_index = 0;

    while (start[i])
    {
        if ((start[i] == '\'' || start[i] == '\"') && !is_inside_quotes)
        {
            is_inside_quotes = 1;
            current_quote = start[i];
            i++;
            continue;
        }
        else if (is_inside_quotes && start[i] == current_quote)
        {
            is_inside_quotes = 0;
            current_quote = 0;
            i++;  // Skip the closing quote
            continue;
        }

        if (!is_inside_quotes || (is_inside_quotes && current_quote == '\"'))
        {
            if (start[i] == '$')
            {
                i++;
                if (start[i] == '?')
                {
                    char *exit_status_str = ft_itoa(ft_exit(4, GET_EXIT_STATUS));
                    if (!exit_status_str)
                    {
                        return NULL;
                    }
                    for (int j = 0; exit_status_str[j]; j++)
                    {
                        if (expanded_index >= expanded_size - 1)
                        {
                            expanded_size *= 2;
                            char *new_expanded_line = realloc(expanded_line, expanded_size);
                            if (!new_expanded_line)
                            {
                                return NULL;
                            }
                            expanded_line = new_expanded_line;
                        }
                        expanded_line[expanded_index++] = exit_status_str[j];
                        // printf("exit_status_str[j] = %c\n", exit_status_str[j]);
                    }
                    i++;
                }
                else if (start[i] == ' ' || start[i] == '\0' || start[i] == '\'' || start[i] == '\"')
                {
                    // Handle $ followed by space or end of string
                    expanded_line[expanded_index++] = '$';
                }
                else
                {
                    printf("HI entered here\n");
                    // Handle variable expansion
                    int varNameLen = 0;
                    while (start[i + varNameLen] && start[i + varNameLen] != ' ' &&
                           start[i + varNameLen] != '\'' && start[i + varNameLen] != '\"' &&
                           start[i + varNameLen] != '/' && start[i + varNameLen] != '$')
                    {
                        varNameLen++;
                    }

                    char *varName = gcalloc(varNameLen + 1);
                    if (!varName)
                    {
                        return NULL;
                    }

                    strncpy(varName, &start[i], varNameLen);
                    varName[varNameLen] = '\0';
                    i += varNameLen;

                    char *value2 = get_env(env, varName);
                    char **splited_value = ft_split_quotes(value2, ' ');

                    char *value = ft_strdup("");
                    printf("before entering\n");

                    for(int i = 0;splited_value[i]; i++)
                    {
                        printf("entered here splited_value[i] = %s\n", splited_value[i]);
                        char *value3 = ft_strjoin("\\", splited_value[i]);
                        char *temp = ft_strjoin(value, value3);
                        value = temp;
                    }
                    if (value)
                    {
                        // Copy the expanded value without quotes
                        int j = 0;
                        while (value[j])
                        {
                            if (value[j] != '\'' && value[j] != '\"')
                            {
                                if (expanded_index >= expanded_size - 1)
                                {
                                    expanded_size *= 2;
                                    char *new_expanded_line = realloc(expanded_line, expanded_size);
                                    if (!new_expanded_line)
                                    {
                                        return NULL;
                                    }
                                    expanded_line = new_expanded_line;
                                }
                                expanded_line[expanded_index++] = value[j];
                            }
                            j++;
                        }
                    }
                }
            }
            else
            {
                if (expanded_index >= expanded_size - 1)
                {
                    expanded_size *= 2;
                    char *new_expanded_line = realloc(expanded_line, expanded_size);
                    if (!new_expanded_line)
                    {
                        return NULL;
                    }
                    expanded_line = new_expanded_line;
                }
                expanded_line[expanded_index++] = start[i++];
            }
        }
        else
        {
            i++; // Skip the character inside single quotes
        }
    }

    expanded_line[expanded_index] = '\0';
    return expanded_line;
}
