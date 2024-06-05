#include "./../frontend.h"
// Just for debug
#include <stdio.h>

// Just for debug
void print_ast_node(t_astnode *node, int indent_level) {
    if (node == NULL)
        return;

    for (int i = 0; i < indent_level; i++) 
        printf("  ");

    switch (node->type) {
        case NODE_COMMAND:
            printf("Command: ");
            for (int i = 0; node->t_cmd.args[i] != NULL; i++) {  // Corrected to access t_cmd
                printf("%s ", node->t_cmd.args[i]);  // Corrected to access t_cmd
            }
            printf("\n");
            break;

        case NODE_PIPE:
            printf("Pipe:\n");
            print_ast_node(node->binary.left, indent_level + 1);  // Corrected to access binary
            print_ast_node(node->binary.right, indent_level + 1);  // Corrected to access binary
            break;

        case NODE_INPUT_REDIRECT:
            printf("Input Redirect: %s\n", node->redirect.filename);  // Corrected to access redirect
            print_ast_node(node->redirect.child, indent_level + 1);  // Corrected to access redirect
            break;

        case NODE_OUTPUT_REDIRECT:
            printf("Output Redirect: %s\n", node->redirect.filename);  // Corrected to access redirect
            print_ast_node(node->redirect.child, indent_level + 1);  // Corrected to access redirect
            break;

        case NODE_SUBSHELL:
            printf("Subshell:\n");
            print_ast_node(node->subshell.child, indent_level + 1);  // Corrected to access subshell
            break;

        default:
            printf("Unknown node type\n");
            break;
    }
}

void print_ast(t_astnode *root) {
    print_ast_node(root, 0);
}
