#include "./../frontend.h"



t_astnode *create_ast_command(int ac, char **av) {
    t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
    node->type = NODE_COMMAND;
    node->t_cmd.cmd = strdup(av[0]);
    node->t_cmd.args = (char **)malloc(sizeof(char *) * (ac + 1));
    for (int i = 0; i < ac; i++) {
        node->t_cmd.args[i] = strdup(av[i]);
    }
    node->t_cmd.args[ac] = NULL;
    node->t_cmd.infile = NULL;
    node->t_cmd.outfile = NULL;
    node->t_cmd.heredoc = NULL;
    node->t_cmd.append = NULL;
    node->t_cmd.flag_infiles = 0;
    node->t_cmd.flag_outfiles = 0;
    return node;
}

t_astnode *create_binary_node(node_type type, t_astnode *left, t_astnode *right) {
    t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
    node->type = type;
    node->binary.left = left;
    node->binary.right = right;
    return node;
}

t_astnode *create_redirect_node(node_type type, t_astnode *child, char *filename) {
    t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
    node->type = type;
    node->redirect.child = child;
    node->redirect.filename = strdup(filename);
    return node;
}
t_astnode *create_block_node(t_astnode *child) {
    t_astnode *node = (t_astnode *)malloc(sizeof(t_astnode));
    node->type = NODE_BLOCK;
    node->block.child = child;
    return node;
}

void print_redirection2(t_redir_list *redir_list, const char *type, int depth) {
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
t_astnode *parse_cmd(t_tklist *tokens) {
    t_token *token;
    int argc = 0;
    char *argv[100];  // Assuming max 100 args

    t_redir_list *infiles = NULL;
    t_redir_list *outfiles = NULL;
    t_redir_list *appends = NULL;
    t_redir_list *heredocs = NULL;

    // Handle leading redirections
    while ((token = peek_token(tokens)) && 
           (token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 || token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
        t_redir *redir = malloc(sizeof(t_redir));
        if (!redir) {
            // Handle memory allocation error
            printf("null in parse_cmd 1\n");
            return NULL;
        }
        redir->file = NULL;
        redir->heredoc = NULL;

        if (token->type == TK_LESSERTHAN1) {
            redir->type = NODE_REDIRECT_IN;
        } else if (token->type == TK_GREATERTHAN1) {
            redir->type = NODE_REDIRECT_OUT;
        } else if (token->type == TK_GREATERTHAN2) {
            redir->type = NODE_REDIRECT_APPEND;
        } else if (token->type == TK_LESSERTHAN2) {
            redir->type = NODE_HEREDOC;
        }

        next_token(tokens); // Consume the redirection token
        token = next_token(tokens); // Get the filename token
        if (!token || token->type != TK_WORD) {
            // Handle error: expected filename after redirection operator
            free(redir);
            printf("null in parse_cmd 2\n");
            return NULL;
        }

        redir->file = token->value;

        t_redir_list *redir_node = malloc(sizeof(t_redir_list));
        if (!redir_node) {
            // Handle memory allocation error
            free(redir);
            printf("null in parse_cmd 3\n");
            return NULL;
        }
        redir_node->redir = redir;
        redir_node->next = NULL;

        if (redir->type == NODE_REDIRECT_IN) {
            printf("add %s\n",redir_node->redir->file);
            ft_lstadd_back_redir(&infiles, redir_node);
            printf("infiles head: %p\n", infiles);
        } else if (redir->type == NODE_REDIRECT_OUT) {
            printf("add %s\n",redir_node->redir->file);

            ft_lstadd_back_redir(&outfiles, redir_node);
        } else if (redir->type == NODE_REDIRECT_APPEND) {
            printf("add %s\n",redir_node->redir->file);

            ft_lstadd_back_redir(&appends, redir_node);
        } else if (redir->type == NODE_HEREDOC) {
            printf("add %s\n",redir_node->redir->file);

            ft_lstadd_back_redir(&heredocs, redir_node);
        }
    }

    // Handle command parsing
    while ((token = peek_token(tokens)) && token->type == TK_WORD) {
        token = next_token(tokens);
        argv[argc++] = token->value;
    }

    if (argc == 0) {
        printf("null in parse_cmd 3\n");
        return NULL;
    }

    t_astnode *cmd_node = create_ast_command(argc, argv);
    cmd_node->t_cmd.infile = infiles;
    cmd_node->t_cmd.outfile = outfiles;
    cmd_node->t_cmd.append = appends;
    cmd_node->t_cmd.heredoc = heredocs;

    while ((token = peek_token(tokens)) && 
           (token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 || token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
        t_redir *redir = malloc(sizeof(t_redir));
        if (!redir) {
            printf("null in create_ast_command 1\n");
            return NULL;
        }
        redir->file = NULL;
        redir->heredoc = NULL;

        if (token->type == TK_LESSERTHAN1) {
            redir->type = NODE_REDIRECT_IN;
        } else if (token->type == TK_GREATERTHAN1) {
            redir->type = NODE_REDIRECT_OUT;
        } else if (token->type == TK_GREATERTHAN2) {
            redir->type = NODE_REDIRECT_APPEND;
        } else if (token->type == TK_LESSERTHAN2) {
            redir->type = NODE_HEREDOC;
        }

        next_token(tokens);
        token = next_token(tokens);
        if (!token || token->type != TK_WORD) {
            free(redir);
            printf("null in create_ast_command 2\n");
            return NULL;
        }

        redir->file = token->value;

        t_redir_list *redir_node = malloc(sizeof(t_redir_list));
        if (!redir_node) {
            free(redir);
            printf("null in create_ast_command 3\n");
            return NULL;
        }
        redir_node->redir = redir;
        redir_node->next = NULL;

        if (redir->type == NODE_REDIRECT_IN) {
            printf("add 2 %s\n",redir_node->redir->file);
            ft_lstadd_back_redir(&infiles, redir_node);
            cmd_node->t_cmd.infile = infiles;
    printf("infiles head: %p\n", infiles);

        } else if (redir->type == NODE_REDIRECT_OUT) {
            printf("add %s\n",redir_node->redir->file);

            ft_lstadd_back_redir(&outfiles, redir_node);
            cmd_node->t_cmd.outfile = outfiles;
        } else if (redir->type == NODE_REDIRECT_APPEND) {
            printf("add %s\n",redir_node->redir->file);

            ft_lstadd_back_redir(&appends, redir_node);
            cmd_node->t_cmd.append = appends;
        } else if (redir->type == NODE_HEREDOC) {
                        printf("add %s\n",redir_node->redir->file);

            ft_lstadd_back_redir(&heredocs, redir_node);
            cmd_node->t_cmd.heredoc = heredocs;
        }
    }
    //         printf("infile %p\n",cmd_node->t_cmd.infile);
    //         printf("outfile %p\n",cmd_node->t_cmd.outfile);
    //         printf("append %p\n",cmd_node->t_cmd.append);
    //         printf("heredoc %p\n",cmd_node->t_cmd.heredoc);

            print_redirection2(cmd_node->t_cmd.infile, "Redirect In",   1);
            print_redirection2(cmd_node->t_cmd.outfile, "Redirect Out",  1);
            print_redirection2(cmd_node->t_cmd.append, "Append Out", 1);
            print_redirection2(cmd_node->t_cmd.heredoc, "Here Document",  1);
    return cmd_node;
}

t_astnode *parse_pipe(t_tklist *tokens) {
    t_astnode *node1 = parse_cmd(tokens);
    if (!node1) {
        // printf("null in parse_pipe 1\n");

        return NULL;
    }

    t_token *token = peek_token(tokens);
    while (token && token->type == TK_PIPE) {
        next_token(tokens);
        t_astnode *node2 = parse_cmd(tokens);
        if (!node2) {
        // printf("null in parse_pipe 2\n");
            return NULL;
        }
        node1 = create_binary_node(NODE_PIPE, node1, node2);
        token = peek_token(tokens);
    }

    return node1;
}

t_astnode *parse_and_or(t_tklist *tokens, t_astnode *left, t_token *token) {
    t_astnode *node = NULL;
    t_astnode *right;

    if (token->type == TK_AND) {
        right = parse_pipe(tokens);
        if (!right) {
        // printf("null in parse_and_or 1\n");

            return NULL;

        }
        node = create_binary_node(NODE_LOGICAL_AND, left, right);
    } else if (token->type == TK_OR) {
        right = parse_pipe(tokens);
        if (!right) {
        // printf("null in parse_and_or 2\n");

            return NULL;

        }
        node = create_binary_node(NODE_LOGICAL_OR, left, right);
    }
    return node;
}
t_astnode *parse_command_line(t_tklist *tokens) {
    t_astnode *node = parse_block(tokens);
    
    if (!node) {
        printf("null in parse_command_line 1\n");
        return NULL;
    }

    t_token *token = peek_token(tokens);
    while (token && (token->type == TK_AND || token->type == TK_OR)) {
        token = next_token(tokens);
        t_astnode *right = parse_command_line(tokens);
        if (!right) {
            printf("null in parse_command_line 2\n");
            return NULL;
        }
        if (token->type == TK_AND) {
            node = create_binary_node(NODE_LOGICAL_AND, node, right);
        } else if (token->type == TK_OR) {
            node = create_binary_node(NODE_LOGICAL_OR, node, right);
        }
        token = peek_token(tokens);
    }
    return node;
}

t_astnode *parse_block(t_tklist *tokens) {
    t_token *token = peek_token(tokens);

    if (token && token->type == TK_LPR) {
        next_token(tokens);
        t_astnode *node = parse_command_line(tokens);
        if (!node) {
            printf("null in parse_block 1\n");
            return NULL;
        }

        token = next_token(tokens);
        if (!token || token->type != TK_RPR) {
            printf("null in parse_block 2\n");
            return NULL;
        }

        t_astnode *block_node = create_block_node(node);
        if (!block_node) {
            printf("null in parse_block 3\n");
            return NULL;
        }
        return block_node;
    } else {
        return parse_pipe(tokens);
    }
}