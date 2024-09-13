#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../minishell.h"
#include "../frontend/frontend.h"
#include <stdlib.h>
#include <string.h>
char *ft_expand_delimiter(char *line, t_lst *env)
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

