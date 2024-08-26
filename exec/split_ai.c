#include <stdio.h>

 char *get_splitted_char(int index)
{
    static  char c[3] = {0, 0, 0}; 

    if (c[index - 1] == 0)
        c[index - 1] = 33; 
    return (&c[index - 1]);
}

void set_splitted_char( char c, int index)
{
     char *splitted_char;

    splitted_char = get_splitted_char(index);
    *splitted_char = c;
}

int check_if_exists( char *str,  char c)
{
    int i = 0;

    if (c == 34 || c == 36 || c == 39) 
        return (1);

    while (str[i]) {
        if (str[i] == c) {
            return (1);
        }
        i++;
    }
    return (0);
}

char get_next_char( char c) {
    if (c < 33)
        return 33;
    else if (c >= 33 && c < 126)
        return (c + 1);
    else if (c == 126)
        return 33; 
    else
        return 33;
}

char which_to_split_with( char **strs, int index)
{
     char c;
    int i;
    int order_of_char;
     char found_char = 0; 
    order_of_char = 0;
    c = get_next_char(32); 
    i = 0;

    while (order_of_char < index)
    {
        i = 0; 
        while (strs[i])
        {
            if (check_if_exists(strs[i], c) || (c != 0 && c == found_char))
            {
                c = get_next_char(c);
                i = 0;
            } else {
                i++;
            }
        }
        order_of_char++;
        found_char = c;
    }
    set_splitted_char(c, index);
    return (c);
}

