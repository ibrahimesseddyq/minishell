#include <stdio.h>

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static int count_words(char *s, char c)
{
    int i;
    int cnt;
    int in_single_quote;
    int in_double_quote;

    i = 0;
    cnt = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    if (!s)
        return (-1);

    while (s[i])
    {
        // Skip delimiters outside of quotes
        while (s[i] == c && s[i])
            i++;
        
        // If we reach a non-delimiter character and are not inside quotes
        if (s[i] && s[i] != c)
        {
            cnt++;
            while (s[i] && (in_single_quote || in_double_quote || s[i] != c))
            {
                if (s[i] == '\'' && !in_double_quote)
                    in_single_quote = !in_single_quote;
                else if (s[i] == '"' && !in_single_quote)
                    in_double_quote = !in_double_quote;
                i++;
            }
        }
    }
    return (cnt);
}

char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t i;

    dup = (char *)malloc(sizeof(char) * (n + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char **ft_split_quotes(char *s, char c)
{
    int i;
    int index;
    int word_length;
    char **arr;
    int in_single_quote;
    int in_double_quote;

    index = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    int tail_matrice = count_words(s, c);
    arr = (char **)malloc((sizeof(char *)) * (tail_matrice + 1));
    if (!arr || tail_matrice == -1)
        return (NULL);

    while (index < tail_matrice)
    {
        i = 0;
        // Skip delimiters outside of quotes
        while (*s && *s == c)
            s++;

        // Determine the length of the next word/segment
        word_length = 0;
        while (s[word_length] && (in_single_quote || in_double_quote || s[word_length] != c))
        {
            if (s[word_length] == '\'' && !in_double_quote)
                in_single_quote = !in_single_quote;
            else if (s[word_length] == '"' && !in_single_quote)
                in_double_quote = !in_double_quote;
            word_length++;
        }
        arr[index] = ft_strndup(s, word_length);
        if (arr[index] == NULL)
        {
            return (NULL);
        }
        s += word_length;
        index++;
    }
    arr[index] = NULL;
    return (arr);
}
