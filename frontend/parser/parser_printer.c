#include "./../frontend.h"
// Just for debug
#include <stdio.h>

// Just for debug
void print_ast(t_astnode *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    switch (node->type) {
        case NODE_COMMAND:
            printf("Command: %s\n", node->t_cmd.cmd);
            for (int i = 0; node->t_cmd.args[i]; i++) {
                for (int j = 0; j < depth + 1; j++) {
                    printf("  ");
                }
                printf("Arg: %s\n", node->t_cmd.args[i]);
            }
            break;
        case NODE_PIPE:
            printf("Pipe:\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_LOGICAL_AND:
            printf("Logical AND:\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_LOGICAL_OR:
            printf("Logical OR:\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_BLOCK:
            printf("Block:\n");
            print_ast(node->block.child, depth + 1);
            break;
        default:
            printf("Unknown node type: %d\n", node->type);
    }
}