#include "./../frontend.h"
// Just for debug

void print_redirection(t_redir *redir, const char *type, int depth) {
    if (!redir) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s:\n", type);

    if (redir->file) {
        for (int j = 0; j < depth + 1; j++) {
            printf("  ");
        }
        printf("File: %s\n", redir->file);
    }
    
    if (redir->heredoc) {
        for (int i = 0; i < depth + 1; i++) {
            printf("  ");
        }
        printf("Here Document: %s\n", redir->heredoc);
    }
    
    for (int i = 0; i < depth + 1; i++) {
        printf("  ");
    }
    printf("Type: %d\n", redir->type);
    
    for (int i = 0; i < depth + 1; i++) {
        printf("  ");
    }
    printf("Number: %d\n", redir->number);
}
void print_ast(t_astnode *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    switch (node->type) {
        case NODE_COMMAND:
            printf("Node Command: %s\n", node->t_cmd.cmd);
            for (int i = 0; node->t_cmd.args[i]; i++) {
                for (int j = 0; j < depth + 1; j++) {
                    printf("  ");
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
        case NODE_REDIRECT_IN:
            printf("Redirect In:\n");
            for (int i = 0; i < depth + 1; i++) {
                printf("  ");
            }
            printf("Filename: %s\n", node->redirect.filename);
            print_ast(node->redirect.child, depth + 1);
            break;
        case NODE_REDIRECT_OUT:
            printf("Redirect Out:\n");
            for (int i = 0; i < depth + 1; i++) {
                printf("  ");
            }
            printf("Filename: %s\n", node->redirect.filename);
            print_ast(node->redirect.child, depth + 1);
            break;
        case NODE_REDIRECT_APPEND:
            printf("Append Out:\n");
            for (int i = 0; i < depth + 1; i++) {
                printf("  ");
            }
            printf("Filename: %s\n", node->redirect.filename);
            print_ast(node->redirect.child, depth + 1);
            break;
        case NODE_HEREDOC:
            printf("Here Document:\n");
            for (int i = 0; i < depth + 1; i++) {
                printf("  ");
            }
            printf("Filename: %s\n", node->redirect.filename);
            print_ast(node->redirect.child, depth + 1);
            break;
        default:
            printf("Unknown node type: %d\n", node->type);
    }
}