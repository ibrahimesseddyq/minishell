#include <stdio.h>



int main()
{
    char old_name[20];
    char new_name[20];

    printf("Enter your name : ");
    scanf("%s", old_name);
    while (1)
    {
        if (old_name[0] == new_name[0])
        {
            printf("Hello Mr.%s\n", old_name);
            break;
        }
        else
        {
            printf("Enter your name : ");
            scanf("%s", new_name);
        }
    }
}