#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minishell.h"
#include "../frontend/frontend.h"
#include <stdlib.h>
#include <string.h>

char *ft_expand_heredoc(char *line, t_lst *env)
{
    int is_inside_quotes = 0;
    char current_quote = 0;
    int len = ft_strlen(line);
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
             if (start[i] == '\"' && is_inside_quotes && current_quote == '\"' && start[i - 1] == '$')
            {
                expanded_line[expanded_index++] = '$';
            }
            is_inside_quotes = 0;
            current_quote = 0;
            i++;
            continue;
        }
        if (!is_inside_quotes || (is_inside_quotes && (current_quote == '\"' || current_quote == '\'')))
        {
            if(is_inside_quotes && start[i] == ' ')
            {
                expanded_line[expanded_index++] = ' ';
                i++;

            }
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
                    }
                    i++;
                }
                else if (start[i] == ' ' || start[i] == '\0' || start[i] == '\'' || start[i] == '\"')
                {
                    if (start[i] == '\"' || start[i] == '\'' && !is_inside_quotes)
                    {
                        continue;
                    }
                    else if(start[i] == ' ')
                    {
                        expanded_line[expanded_index++] = '$';
                        expanded_line[expanded_index++] = ' ';
                    }
                    else if(is_inside_quotes)
                    {
                        expanded_line[expanded_index++] = '$';
                    }
                    i++;
                }
                else
                {

                    int varNameLen = 0;
                    while (start[i + varNameLen] && start[i + varNameLen] != ' ' &&
                           start[i + varNameLen] != '\'' && start[i + varNameLen] != '\"' &&
                           start[i + varNameLen] != '/' && start[i + varNameLen] != '$' && start[i + varNameLen] != '=')
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

                    char *value2 = ft_strdup(get_env(env, varName));
                    char *value = value2;
                    for(int i = 0; value[i] && !is_inside_quotes; i++)
                    {
                        if(value[i] == ' ' && !is_inside_quotes)
                            value[i] = *get_splitted_char(2);
                    }
                    if (value)
                    {
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
    }

    expanded_line[expanded_index] = '\0';
    return expanded_line;
}
