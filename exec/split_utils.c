#include <stdlib.h>
#include <string.h>

// Helper function to count occurrences of a delimiter in a string
static int count_delimiter_occurrences(char *s, char delimiter) {
    int count = 0;
    while (*s) {
        if (*s == delimiter) {
            count++;
        }
        s++;
    }
    return count;
}

// Helper function to split a single string using a delimiter
static char **split_string(char *s, char delimiter) {
    int count = count_delimiter_occurrences(s, delimiter) + 1;
    char **result = malloc((count + 1) * sizeof(char *));
    if (!result) return NULL;

    int index = 0;
    char *start = s;
    char *end;

    while ((end = strchr(start, delimiter)) != NULL) {
        result[index] = strndup(start, end - start);
        if (!result[index])
        {
            return NULL;
        }
        index++;
        start = end + 1;
    }

    result[index] = strdup(start); // Last segment
    if (!result[index]) {
        return NULL;
    }
    result[++index] = NULL; // Null-terminate the result array
    return result;
}

// Function to split all strings in the given array
char **split_all_strings(char **array, char delimiter)
{
    if (!array) return NULL;

    int total_count = 0;
    for (int i = 0; array[i]; i++) {
        total_count += count_delimiter_occurrences(array[i], delimiter) + 1;
    }

    char **result = malloc((total_count + 1) * sizeof(char *));
    if (!result) return NULL;

    int result_index = 0;
    for (int i = 0; array[i]; i++) {
        char **split_result = split_string(array[i], delimiter);
        if (!split_result) {
            return NULL;
        }

        for (int k = 0; split_result[k]; k++) {
            result[result_index++] = split_result[k];
        }

    }
    result[result_index] = NULL; // Null-terminate the result array
    return result;
}
