#include "./../frontend.h"
// typedef struct s_astnode
// {
// 	node_type type;
//     union {
//         struct
// 		{
//             char** argv;
//             int argc;
//         } cmd;

//         struct
// 		{
//             struct ast_node* left;
//             struct ast_node* right;
//         } binary;

//         struct
// 		{
//             struct ast_node* child;
//             char* filename;
//             int mode;
//         } redirect;

//         struct
// 		{
//             struct ast_node* child;
//         } subshell;
//     };
// } t_astnode;
t_astnode *create_ast_command(t_token *token, int ac, char **av)
{
	t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
	int i = 0;
	node->type = NODE_COMMAND;
	node->cmd.argv = (char **)malloc(sizeof(char *));
	node->cmd.argc = ac;
	while(i < ac)
	{
		node->cmd.argv[i] = ft_strdup(av[i]);
		i++;
	}
	return (node);
}
t_astnode *place_ast(t_astnode *node, t_astnode *root)
{
	if(NULL == root)
		return node;
	if (node->type == NODE_PIPE)
	{
		t_astnode *tmp = root;
	}
}
t_astnode *parse(t_token **tokens)
{
	int ac;
	char **av;
	int i = 0;
	int j = 0;
	t_astnode **root;

	while(tokens[i])
	{
		if(tokens[i]->type == TK_COMMAND)
		{
			ac++;
			av[j++] = tokens[i]->value;
			root = place_ast(create_ast_command(tokens[i], ac, av));
		}
		else if(tokens[i]->type == TK_PIPE)
		{

		}
		else if(tokens[i]->type == TK_SEMICOLON)
		{
			
		}
		else if(tokens[i]->type == TK_LPR)
		{
			
		}
		else if(tokens[i]->type == TK_RPR)
		{
			
		}
		else if(tokens[i]->type == TK_ILLEGAL)
		{
			
		}
		else if(tokens[i]->type == TK_AND1)
		{
			
		}
		else if(tokens[i]->type == TK_AND2)
		{
			
		}
		else if(tokens[i]->type == TK_GREATERTHAN1)
		{
			
		}
		else if(tokens[i]->type == TK_GREATERTHAN2)
		{
			
		}
		else if(tokens[i]->type == TK_LESSERTHAN1)
		{
			
		}
		else if(tokens[i]->type == TK_LESSERTHAN2)
		{
			
		}
		else if(tokens[i]->type == TK_WORD)
		{
			
		}
		else if(tokens[i]->type == TK_EQUAL)
		{
			
		}
		else if(tokens[i]->type == TK_PLUS)
		{
			
		}
		i++;
	}
}