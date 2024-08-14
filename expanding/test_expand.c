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
    int expanded_size = 64;
    char *expanded_line = malloc(expanded_size);
    if (!expanded_line) return NULL;
    int expanded_index = 0;

    while (start[i])
    {
        if ((start[i] == '\'' || start[i] == '\"') && !is_inside_quotes)
        {
            is_inside_quotes = 1;
            current_quote = start[i];
            i++;  // Skip the opening quote
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
                // Handle variable expansion
                i++;
                if (start[i] == '?')
                {
                    // Handle $? expansion
                    // ... (existing code for $? expansion)
                }
                else if (start[i] == ' ' || start[i] == '\0' || start[i] == '\'' || start[i] == '\"')
                {
                    // Handle $ followed by space or end of string
                    expanded_line[expanded_index++] = '$';
                }
                else
                {
                    // Handle variable expansion
                    int varNameLen = 0;
                    while (start[i + varNameLen] && start[i + varNameLen] != ' ' &&
                           start[i + varNameLen] != '\'' && start[i + varNameLen] != '\"' &&
                           start[i + varNameLen] != '/' && start[i + varNameLen] != '$') {
                        varNameLen++;
                    }

                    char *varName = malloc(varNameLen + 1);
                    if (!varName)
                    {
                        return NULL;
                    }

                    strncpy(varName, &start[i], varNameLen);
                    varName[varNameLen] = '\0';
                    i += varNameLen;

                    char *value = get_env(env, varName);
                    if (value)
                    {
                        // Copy the expanded value without quotes
                        while (*value)
                        {
                            if (*value != '\'' && *value != '\"')
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
                                expanded_line[expanded_index++] = *value;
                            }
                            value++;
                        }
                    }
                }
            }
            else
            {
                // Copy non-$ characters
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
            // Inside single quotes, copy literally
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

    expanded_line[expanded_index] = '\0';
    return expanded_line;
}