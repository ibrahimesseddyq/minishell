#include "./../frontend.h"
// Just for debug
void print_ast_node(t_astnode *node, int indent_level)
{
						printf("COMMAND");
    if (node == NULL)
        return;
					printf("COMMAND");

    for (int i = 0; i < indent_level; i++) 
        printf("  ");

    switch (node->type) 
	{
        case NODE_COMMAND:
            printf("Command: ");
            for (int i = 0; i < node->cmd.argc; i++)
			{
                printf("%s ", node->cmd.argv[i]);
            }
            printf("\n");
            break;

        case NODE_PIPE:
            printf("Pipe:\n");
            print_ast_node(node->binary.left, indent_level + 1);
            print_ast_node(node->binary.right, indent_level + 1);
            break;

        case NODE_INPUT_REDIRECT:
            printf("Input Redirect: %s\n", node->redirect.filename);
            print_ast_node(node->redirect.child, indent_level + 1);
            break;

        case NODE_OUTPUT_REDIRECT:
            printf("Output Redirect: %s\n", node->redirect.filename);
            print_ast_node(node->redirect.child, indent_level + 1);
            break;

        case NODE_SUBSHELL:
            printf("Subshell:\n");
            print_ast_node(node->subshell.child, indent_level + 1);
            break;

        default:
            printf("Unknown node type\n");
            break;
    }
}

void print_ast(t_astnode *root)
{
    print_ast_node(root, 0);
}