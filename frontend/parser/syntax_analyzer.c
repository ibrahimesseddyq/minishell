#include "./../frontend.h"

//c\n  1  2  3  4  5  6  7  8  9  10 11
//     -  -  -  -  -  -  -  -  -  -  -
// 1 |-1  1 -1 -1 -1 -1  3  3  3  3  2
// 2 |-1  1 -1 -1 -1 -1  3  3  3  3  2
// 3 |-1 -1  4  8  7  6  3  3  3  3  2
// 4 |-1 -1 -1 -1 -1 -1 -1 -1 -1 -1  2
// 5 |-1 -1  4  8  7  6  5  5  5  5 -1
// 6 |-1 -1 -1 -1 -1 -1 -1 -1 -1 -1  4
// 7 |-1  1 -1 -1 -1 -1  3  3  3  3  2
// 8 |-1  1 -1 -1 -1 -1  3  3  3  3  2
// 9 |-1  1 -1 -1 -1 -1  3  3  3  3  2

int analyse_syntax(t_tklist *list)
{
    // t_token *tokens;
    char    *final_token;
    int     curr_token;
    t_token *token;
    int parentheses;
    int e;
    static int	tr[9][11] = 
    {{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
    {-1, -1, 4, 8, 7, 6, 3, 3, 3, 3, 2},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2},
	{-1, -1, 4, 8, 7, 6, 5, 5, 5, 5, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},

	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2},
	{-1, 1, -1, -1, -1, -1, 3, 3, 3, 3, 2}};

    parentheses = 0;
    e = 0;
    token = NULL;
    // tokens = list->tokens;
    curr_token = next_token(list)->type;
    if (!curr_token)
        return (0);
    if (curr_token == TK_LPR)
        parentheses++;
    // if (curr_token == -1)
    //     bzero(final_token, ft_strlen(final_token));
    while(tr[e][curr_token] != -1 && curr_token > 0)
    {
        e = tr[e][curr_token];
        token = next_token(list);
        curr_token = token->type;
        final_token = token->value;
            // printf("curr token %d parentheses %d and e %d\n",curr_token, parentheses, e);

        if (curr_token == TK_LPR)
             parentheses++;
        
        if (curr_token == TK_RPR)
        {
            if(parentheses > 0)
                parentheses--;
            else 
                curr_token = -1;
        }
    }
    // printf("end - curr token %d parentheses %d and e %d\n",curr_token, parentheses, e);
    if (curr_token == 0 && parentheses == 0 && (e == 2 || e ==4))
    {
        return (1);
    }
    else
    {
        printf("Minishell: syntax error near unexpected token `%s'\n",final_token);
        return (0);
    }
}