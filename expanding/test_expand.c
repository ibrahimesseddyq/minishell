#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to get the last exit code (placeholder implementation)
char get_last_exit_code() {
    return '1'; // This should be replaced with the actual last exit code logic
}

// Function to expand variables in the input line
void ft_expand(char *line) {
    int is_inside_quotes = 0;
    char current_quote = 0;
    char *start = line;
    int i = 0;

    while (start[i]) {
        if (start[i] == '\'' || start[i] == '\"') {
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

        if ((is_inside_quotes == 0 || (is_inside_quotes == 1 && current_quote == '\"')) && start[i] == '$') {
            i++;
            if (start[i] == '?') {
                printf("%d", get_last_exit_code());
                i++;
            } else if (start[i] == '$') {
                printf("%d", getpid());
                i++;
            } else if (start[i] == ' ' || start[i] == '\0') {
                printf("$");
            } else {
                char varName[256] = {0};
                int j = 0;
                while (start[i] != ' ' && start[i] != '\0' && start[i] != '\'' && start[i] != '\"') {
                    varName[j++] = start[i++];
                }
                varName[j] = '\0';

                char *value = getenv(varName);
                if (value) {
                    printf("%s", value);
                } else {
                    // Handle variable not existing
                    printf("$%s", varName);
                }
            }
        } else {
            putchar(start[i]);
            i++;
        }
    }
}


// int main(int argc, char **argv) {
//     char *line = strdup("\"$$\" $$ \"$USER\" $UNKNOWN $?");
//     ft_expand(line);
//     printf("\nmy pid: %d\n", getpid());
//     free(line);
//     return 0;
// }
