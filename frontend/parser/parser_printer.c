#include "./../frontend.h"
// Just for debug

void print_redirection(t_redir_list *redir_list, const char *type, int depth) {
        // printf("HI2\n");

    if (!redir_list) return;
    t_redir_list *current = redir_list;

    while (current) {
        // printf("HI\n");
        t_redir *redir = current->redir;
        for (int i = 0; i < depth; i++) {
            printf(" ");
        }
        printf("%s:\n", type);
        if (redir->file) {
            for (int i = 0; i < depth + 1; i++) {
                printf(" ");
            }
            printf("File: %s\n", redir->file);
        }
        if (redir->heredoc) {
            for (int i = 0; i < depth + 1; i++) {
                printf(" ");
            }
            printf("Here Document: %s\n", redir->heredoc);
        }
        for (int i = 0; i < depth + 1; i++) {
            printf(" ");
        }
        printf("Type: %d\n", redir->type);
        current = current->next;
    }
}

void print_ast(t_astnode *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    switch (node->type) {
        case NODE_COMMAND:
            printf("Node Command: %s\n", node->t_cmd.cmd);
            for (int i = 0; node->t_cmd.args[i]; i++) {
                for (int j = 0; j < depth + 1; j++) {
                    printf(" ");
                }
                printf("Arg: %s\n", node->t_cmd.args[i]);
            }
            print_redirection(node->t_cmd.infile, "Redirect In", depth + 1);
            print_redirection(node->t_cmd.outfile, "Redirect Out", depth + 1);
            print_redirection(node->t_cmd.append, "Append Out", depth + 1);
            print_redirection(node->t_cmd.heredoc, "Here Document", depth + 1);
            break;
        case NODE_PIPE:
            printf("Node Pipe:\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_LOGICAL_AND:
            printf("Node Logical AND:\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_LOGICAL_OR:
            printf("Node Logical OR:\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_BLOCK:
            printf("Node Block:\n");
            print_ast(node->block.child, depth + 1);
            break;
        default:
            printf("Unknown node type: %d\n", node->type);
    }
}