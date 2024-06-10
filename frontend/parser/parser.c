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


t_astnode *parse_cmd(t_tklist *tokens) {
    t_token *token;
    int argc = 0;
    char *argv[100]; 

    while ((token = peek_token(tokens)) && token->type == TK_WORD) {
        token = next_token(tokens);
        argv[argc++] = token->value;
    }

    if (argc == 0) {
        return NULL;
    }

    t_astnode *cmd_node = create_ast_command(argc, argv);

    while ((token = peek_token(tokens)) && (token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 || token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
        node_type redirect_type;
        if (token->type == TK_LESSERTHAN1) {
            redirect_type = NODE_REDIRECT_IN;
        } else if (token->type == TK_GREATERTHAN1) {
            redirect_type = NODE_REDIRECT_OUT;
        } else if (token->type == TK_GREATERTHAN1) {
            redirect_type = NODE_REDIRECT_APPEND;
        } else if (token->type == TK_LESSERTHAN2) {
            redirect_type = NODE_HEREDOC;
        }

        next_token(tokens);
        token = next_token(tokens);
        if (!token || token->type != TK_WORD) {
            return NULL;
        }

        cmd_node = create_redirect_node(redirect_type, cmd_node, token->value);
    }

    return cmd_node;
}

t_astnode *parse_pipe(t_tklist *tokens) {
    t_astnode *node1 = parse_cmd(tokens);
    if (!node1) {
        return NULL;
    }

    t_token *token = peek_token(tokens);
    while (token && token->type == TK_PIPE) {
        next_token(tokens);
        t_astnode *node2 = parse_cmd(tokens);
        if (!node2) {
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
            return NULL;
        }
        node = create_binary_node(NODE_LOGICAL_AND, left, right);
    } else if (token->type == TK_OR) {
        right = parse_pipe(tokens);
        if (!right) {
            return NULL;
        }
        node = create_binary_node(NODE_LOGICAL_OR, left, right);
    }

    return node;
}

t_astnode *parse_command_line(t_tklist *tokens) {
    t_astnode *node = parse_pipe(tokens);
    if (!node) {
        return NULL;
    }

    t_token *token = peek_token(tokens);
    while (token && (token->type == TK_AND || token->type == TK_OR)) {
        token = next_token(tokens);
        node = parse_and_or(tokens, node, token);
        if (!node) {
            return NULL;
        }
        token = peek_token(tokens);
    }

    while ((token = peek_token(tokens)) && (token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 || token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
        node_type redirect_type;
        if (token->type == TK_LESSERTHAN1) {
            redirect_type = NODE_REDIRECT_IN;
        } else if (token->type == TK_GREATERTHAN1) {
            redirect_type = NODE_REDIRECT_OUT;
        } else if (token->type == TK_GREATERTHAN2) {
            redirect_type = NODE_REDIRECT_APPEND;
        } else if (token->type == TK_LESSERTHAN2) {
            redirect_type = NODE_HEREDOC;
        }

        next_token(tokens);
        token = next_token(tokens);
        if (!token || token->type != TK_WORD) {
            return NULL;
        }

        node = create_redirect_node(redirect_type, node, token->value);
    }

    return node;
}

t_astnode *inside_block(t_tklist *tokens, t_astnode **node) {
    *node = parse_command_line(tokens);
    if (!*node) {
        return NULL;
    }

    t_token *token = next_token(tokens);
    if (token && token->type != TK_RPR) {
        return NULL;
    }

    while ((token = peek_token(tokens)) && (token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 || token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
        node_type redirect_type;
        if (token->type == TK_LESSERTHAN1) {
            redirect_type = NODE_REDIRECT_IN;
        } else if (token->type == TK_GREATERTHAN1) {
            redirect_type = NODE_REDIRECT_OUT;
        } else if (token->type == TK_GREATERTHAN2) {
            redirect_type = NODE_REDIRECT_APPEND;
        } else if (token->type == TK_LESSERTHAN2) {
            redirect_type = NODE_HEREDOC;
        }

        next_token(tokens);
        token = next_token(tokens);
        if (!token || token->type != TK_WORD) {
            return NULL;
        }

        *node = create_redirect_node(redirect_type, *node, token->value);
    }

    return *node;
}

t_astnode *parse_block(t_tklist *tokens) {
    t_astnode *node = NULL;
    t_astnode *cmd_node = NULL;
    t_token *token;
    int redirect_type;
    char *filename;

    if (peek_token(tokens)->type == TK_LPR) {
        next_token(tokens);

        cmd_node = parse_command_line(tokens);
        if (!cmd_node) {
            return NULL;
        }

        if (next_token(tokens)->type != TK_RPR) {
            return NULL;
        }

        node = create_block_node(cmd_node);

        while ((token = peek_token(tokens)) &&
               (token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 ||
                token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
            if (token->type == TK_LESSERTHAN1) {
                redirect_type = NODE_REDIRECT_IN;
            } else if (token->type == TK_GREATERTHAN1) {
                redirect_type = NODE_REDIRECT_OUT;
            } else if (token->type == TK_GREATERTHAN2) {
                redirect_type = NODE_REDIRECT_APPEND;
            } else if (token->type == TK_LESSERTHAN2) {
                redirect_type = NODE_HEREDOC;
            }

            next_token(tokens); // Consume the redirection token

            token = next_token(tokens); // Get the filename token
            if (!token || token->type != TK_WORD) {
                // Handle error: expected filename after redirection operator
                return NULL;
            }

            filename = token->value;
            node = create_redirect_node(redirect_type, node, filename);
        }
    } else {
        node = parse_command_line(tokens);
    }

    return node;
}