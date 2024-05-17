#include "./../frontend.h"

t_astnode *create_ast_command(int ac, char **av)
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
t_astnode	 *create_binary_node(node_type type, t_astnode *left, t_astnode *right)
{
	t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
	node->type = type;
	node->binary.left = left;
	node->binary.right = right;
	return (node);
}
t_astnode *create_redirect_node(node_type type, t_astnode *child, char *filename, int mode)
{
	t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
	node->type = type;
	node->redirect.child = child;
	node->redirect.filename = ft_strdup(filename);
	node->redirect.mode = mode;
	return (node);
}
t_astnode *create_subshell_node(t_astnode *child)
{
	t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
	node->type = NODE_SUBSHELL;
	node->subshell.child  = child;
	return (node);
}
t_astnode *parse_command(t_tklist *tokenlist, t_token **current_token)
{
	    // printf("\n1 - TOKEN: {%s}\n", (*current_token)->value);

    if ((*current_token)->type != TK_COMMAND && (*current_token)->type != TK_WORD)
    {
        return NULL;
    }
    int argc = 0;
    char **argv;
    int i = 0;

    t_token *temptk = *current_token;
    while (temptk->type == TK_COMMAND || temptk->type == TK_WORD)
    {
        argc++;
        temptk = peek_next_token(tokenlist, i + 1);
        i++;
    }

    argv = (char **)malloc(sizeof(char *) * argc);
    i = 0;
    while (i < argc)
    {
        argv[i] = strdup((*current_token)->value);

        *current_token = next_token(tokenlist);
        i++;
    }

    return create_ast_command(argc, argv);
}

t_astnode *parse_redirection(t_tklist *tokenlist, t_astnode *command, t_token **current_token)
{
    if ((*current_token)->type == TK_GREATERTHAN1 || (*current_token)->type == TK_GREATERTHAN2 ||
        (*current_token)->type == TK_LESSERTHAN1 || (*current_token)->type == TK_LESSERTHAN2)
    {
        node_type type = ((*current_token)->type == TK_GREATERTHAN1 || (*current_token)->type == TK_GREATERTHAN2)
                             ? NODE_OUTPUT_REDIRECT
                             : NODE_INPUT_REDIRECT;
        int mode = ((*current_token)->type == TK_GREATERTHAN2 || (*current_token)->type == TK_LESSERTHAN2) ? 2 : 1;
        *current_token = next_token(tokenlist);
        if ((*current_token)->type != TK_WORD)
            return NULL;
        char *filename = strdup((*current_token)->value);
        *current_token = next_token(tokenlist);
        return create_redirect_node(type, command, filename, mode);
    }
    return command;
}

t_astnode* parse_pipeline(t_tklist *token_list, t_token **current_token)
{

    t_astnode* command = parse_command(token_list, current_token);

    command = parse_redirection(token_list, command, current_token);

    while ((*current_token)->type == TK_PIPE)
    {

        *current_token = next_token(token_list); // consume '|'

        t_astnode* next_command = parse_command(token_list, current_token);
		    // printf("\n3 - TOKEN: {%s}\n", (next_command)->cmd.argv[1]);

        next_command = parse_redirection(token_list, next_command, current_token);

        command = create_binary_node(NODE_PIPE, command, next_command);
				    // printf("\n1 - TOKEN: hhh {%s}\n", (command)->binary.left->cmd.argv[0]);
    }
			    printf("\n6 - TOKEN: {%s}\n", (command)->binary.right->redirect.child->cmd.argv[0]);

    return command;
}

t_astnode* parse_subshell(t_tklist *token_list, t_token **current_token)
{
    if ((*current_token)->type == TK_LPR)
    {
        *current_token = next_token(token_list); // consume '('
        t_astnode* command_list = parse_pipeline(token_list, current_token);
        if ((*current_token)->type != TK_RPR)
        {
            return NULL;
        }
        *current_token = next_token(token_list); // consume ')'
        return create_subshell_node(command_list);
    }
    return parse_pipeline(token_list, current_token);
}

t_astnode* parse_logical_expression(t_tklist *token_list, t_token **current_token)
{
    t_astnode* command = parse_subshell(token_list, current_token);



    while ((*current_token)->type == TK_AND1 || (*current_token)->type == TK_AND2 || (*current_token)->type == TK_OR)
    {

        node_type type = ((*current_token)->type == TK_AND1 || (*current_token)->type == TK_AND2) ? NODE_LOGICAL : NODE_SEQUENCE;
        *current_token = next_token(token_list); // consume '&&' or '||'
        t_astnode* next_command = parse_subshell(token_list, current_token);
        command = create_binary_node(type, command, next_command);

    }
    return command;
}

t_astnode* parse_sequence(t_tklist *token_list, t_token **current_token)
{

    t_astnode* command = parse_logical_expression(token_list, current_token);

    while ((*current_token)->type == TK_SEMICOLON)
    {

        *current_token = next_token(token_list); // consume ';'
        t_astnode* next_command = parse_logical_expression(token_list, current_token);
        command = create_binary_node(NODE_SEQUENCE, command, next_command);

    }
    return command;
}

t_astnode* parse_command_list(t_tklist *token_list)
{
    t_token* current_token = peek_token(token_list); // Initialize current_token without advancing
    // printf("\n1 - TOKEN: {%s}\n", current_token->value);
    t_astnode* command_list = parse_sequence(token_list, &current_token);

    if (current_token->type != TOKEN_EOF)
    {
        return NULL;
    }
    return command_list;
}

// t_astnode *parse_command(t_tklist *tokenlist, t_token **current_token)
// {
//     if ((*current_token)->type != TK_COMMAND && (*current_token)->type != TK_WORD)
//     {
//         return NULL;
//     }
//     int argc = 0;
//     char **argv;
//     int i = 0;

//     t_token *temptk = *current_token;
//     while (temptk->type == TK_COMMAND || temptk->type == TK_WORD)
//     {
//         argc++;
//         temptk = peek_next_token(tokenlist, i + 1);
//         i++;
//     }

//     argv = (char **)malloc(sizeof(char *) * argc);
//     i = 0;
//     while (i < argc)
//     {
//         argv[i] = strdup((*current_token)->value);
// 		printf("arg : \n{%s}\n",argv[i]);
//         *current_token = next_token(tokenlist);
// 				// printf("COMMAND[%s]\n",argv[i]);
//         i++;
//     }
// 		printf("\n");
//     return create_ast_command(argc, argv);
// }

// t_astnode *parse_redirection(t_tklist *tokenlist, t_astnode *command, t_token **current_token)
// {
//     if ((*current_token)->type == TK_GREATERTHAN1 || (*current_token)->type == TK_GREATERTHAN2 ||
//         (*current_token)->type == TK_LESSERTHAN1 || (*current_token)->type == TK_LESSERTHAN2)
//     {
//         node_type type = ((*current_token)->type == TK_GREATERTHAN1 || (*current_token)->type == TK_GREATERTHAN2)
//                              ? NODE_OUTPUT_REDIRECT
//                              : NODE_INPUT_REDIRECT;
//         int mode = ((*current_token)->type == TK_GREATERTHAN2 || (*current_token)->type == TK_LESSERTHAN2) ? 2 : 1;
//         *current_token = next_token(tokenlist);
//         if ((*current_token)->type != TK_WORD)
//             return NULL;
//         char *filename = strdup((*current_token)->value);
// 		printf("\ncommand redirect :{%d}, filename: {%s}\n",5,filename);
//         *current_token = next_token(tokenlist);
//         return create_redirect_node(type, command, filename, mode);
//     }
//     return command;
// }

// t_astnode* parse_pipeline(t_tklist *token_list, t_token **current_token)
// {
//     t_astnode* command = parse_command(token_list, current_token);
//     command = parse_redirection(token_list, command, current_token);
// 	if(command)
// 	{
// 				printf("\n ts command: {%s}\n",command->cmd.argv[0]);

// 	}

//     while ((*current_token)->type == TK_PIPE)
// 	{
// 					// printf("\n5.2 -TOKEN:{%s}\n",(*current_token)->value);

//         *current_token = next_token(token_list); // consume '|'
//         t_astnode* next_command = parse_command(token_list, current_token);
//         next_command = parse_redirection(token_list, next_command, current_token);
//         command = create_binary_node(NODE_PIPE, command, next_command);
//     }
//     return command;
// }

// t_astnode* parse_subshell(t_tklist *token_list, t_token **current_token)
// {
//     if ((*current_token)->type == TK_LPR)
// 	{
//         *current_token = next_token(token_list); // consume '('
//         t_astnode* command_list = parse_pipeline(token_list, current_token);
//         if ((*current_token)->type != TK_RPR)
// 		{
//             return NULL;
//         }
//         *current_token = next_token(token_list); // consume ')'
//         return create_subshell_node(command_list);
//     }
//     return parse_pipeline(token_list, current_token);
// }

// t_astnode* parse_logical_expression(t_tklist *token_list, t_token **current_token)
// {
//     t_astnode* command = parse_subshell(token_list, current_token);
// 				// printf("\n3.1 -TOKEN:{%s}\n",(*current_token)->value);

// 		// if(command)
// 		// {
// 		// 	printf("\nyes4, token : %s\n",(*current_token)->value);
// 		// }
// 		// else
// 		// {
// 		// 	printf("\nno4\n");
// 		// }
//     while ((*current_token)->type == TK_AND1 || (*current_token)->type == TK_AND2 || (*current_token)->type == TK_OR)
// 	{
// 					printf("\n3.2 -TOKEN:{%s}\n",(*current_token)->value);

//         node_type type = ((*current_token)->type == TK_AND1 || (*current_token)->type == TK_AND2) ? NODE_LOGICAL : NODE_SEQUENCE;
//         *current_token = next_token(token_list); // consume '&&' or '||'
//         t_astnode* next_command = parse_subshell(token_list, current_token);
//         command = create_binary_node(type, command, next_command);
// 		// 		if(command)
// 		// {
// 		// 	printf("\nyes3, token : %s\n",(*current_token)->value);
// 		// }
// 		// else
// 		// {
// 		// 	printf("\nno3\n");
// 		// }
//     }
//     return command;
// }

// t_astnode* parse_sequence(t_tklist *token_list, t_token **current_token)
// {
// 				// printf("\n2.1 -TOKEN:{%s}\n",(*current_token)->value);

//     t_astnode* command = parse_logical_expression(token_list, current_token);
// 		// if(command)
// 		// {
// 		// 	printf("\nyes2, token : %s\n",(*current_token)->value);
// 		// }
// 		// else
// 		// {
// 		// 	printf("\nno2\n");
// 		// }
//     while ((*current_token)->type == TK_SEMICOLON)
// 	{
// 			printf("\n2.2 -TOKEN:{%s}\n",(*current_token)->value);

//         *current_token = next_token(token_list); // consume ';'
//         t_astnode* next_command = parse_logical_expression(token_list, current_token);
//         command = create_binary_node(NODE_SEQUENCE, command, next_command);
// 		// if(command)
// 		// {
// 		// 	printf("\nyes1, token : %s\n",(*current_token)->value);
// 		// }
// 		// else
// 		// {
// 		// 	printf("\nno1\n");
// 		// }
//     }
//     return command;
// }

// t_astnode* parse_command_list(t_tklist *token_list)
// {
//     t_token* current_token = next_token(token_list);
//     t_astnode* command_list = parse_sequence(token_list, &current_token);

//     if (current_token->type != TOKEN_EOF)
// 	{
//         return NULL;
//     }
//     return command_list;
// }