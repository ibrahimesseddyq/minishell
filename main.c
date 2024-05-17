#include "minishell.h"
#include "./frontend/frontend.h"
int main(int ac, char **av)
{
	(void)av;
	(void)(ac);
	t_tklist *tklist;
	t_list *lst;
	// t_astnode *root;

	tklist =malloc(sizeof(t_tklist));
	lst = lex(add_spaces("echo hello | grep h > file1.txt |  sort"));
	// tklist->tokens = lst;
	// tklist->curr_index = 0;
	// root =parse_command_list(tklist);
	// print_ast(root);
	test_lexer(lst);
	// printf("[%s]\n",add_spaces("ls > a >>> ( ls >& && || | ) ls"));
	// printf("[%s]",add_spaces("ls>a>>>(ls>&&&|||)ls"));

}
// #include "./frontend.h"

// int main() {
//     // Example setup of a complex token list
//     t_tklist token_list;
//     t_list tokens[25];
//     t_token token_data[25] = {
//         {TK_COMMAND, "echo"},
//         {TK_WORD, "hello"},
//         {TK_AND1, "&&"},
//         {TK_COMMAND, "echo"},
//         {TK_WORD, "world"},
//         {TK_GREATERTHAN1, ">"},
//         {TK_WORD, "out1.txt"},
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
