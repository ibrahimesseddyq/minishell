
#include "../frontend.h"
#include "./../../libft/libft.h"
void printlex(void *content) {
    t_token *token = (t_token *)content;
    if (token->value) {
        printf("[%s - <%u>]\n", token->value, token->type);
    }
}

void test_lexer(t_list *lst)
{
	ft_lstiter(lst,printlex);

}