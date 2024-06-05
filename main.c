#include "minishell.h"
#include "./frontend/frontend.h"
int main() {
    char input[] = "echo Hello World && ls -l | grep 'txt' > output.txt";
    t_tklist *token_list = tokenize(input);
    print_tokens(token_list);

    // Free allocated memory
    for (int i = 0; i < token_list->size; i++) {
        free(token_list->tokens[i].value);
    }
    free(token_list->tokens);
    free(token_list);

    return 0;
}


// int main() {
//     // Example setup of a complex token list
//     t_tklist token_list;
//     t_list tokens[25];
//     t_token token_data[25] = {
//         {TK_LPR, "("},
//         {TK_COMMAND, "echo"},
//         {TK_WORD, "hello"},
//         {TK_AND1, "&&"},
//         {TK_COMMAND, "echo"},
//         {TK_WORD, "world"},
//         {TK_GREATERTHAN1, ">"},
//         {TK_WORD, "out1.txt"},
//         {TK_RPR, ")"},
//         {TK_OR, "||"},
//         {TK_LPR, "("},
//         {TK_COMMAND, "cat"},
//         {TK_WORD, "out1.txt"},
//         {TK_PIPE, "|"},
//         {TK_COMMAND, "grep"},
//         {TK_WORD, "hello"},
//         {TK_GREATERTHAN2, ">>"},
//         {TK_WORD, "out2.txt"},
//         {TK_RPR, ")"},
//         {TK_AND1, "&&"},
//         {TK_COMMAND, "echo"},
//         {TK_WORD, "done"},
//         {TK_GREATERTHAN1, ">"},
//         {TK_WORD, "out3.txt"},
//         {TOKEN_EOF, NULL}
//     };

//     // Setting up the linked list of tokens
//     for (int i = 0; i < 24; i++) {
//         tokens[i].content = &token_data[i];
//         tokens[i].next = (i < 23) ? &tokens[i + 1] : NULL;
//     }
//     token_list.tokens = &tokens[0];
//     token_list.curr_index = 0;

//     t_astnode *root = parse_command_list(&token_list);
//     if (root == NULL) {
//         printf("Parsing failed\n");
//         return 1;
//     }

//     // Print the AST
//     print_ast(root);

//     // Free the AST (not implemented here)
//     // free_ast(root);

//     return 0;
// }
