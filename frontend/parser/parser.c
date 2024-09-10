#include "./../frontend.h"



t_astnode *create_ast_command(int ac, char **av)
{
    t_astnode *node = (t_astnode *)gcalloc(sizeof(t_astnode));
    node->type = NODE_COMMAND;
    node->t_cmd.cmd = strdup(av[0]);
    node->t_cmd.args = NULL;

    t_arg_node *current = NULL;
    for (int i = 0; i < ac; i++)
    {
        t_arg_node *new_node = (t_arg_node *)gcalloc(sizeof(t_arg_node));
        new_node->arg = strdup(av[i]);
        new_node->next = NULL;

        if (node->t_cmd.args == NULL)
        {
            node->t_cmd.args = new_node;
            current = new_node;
        }
        else
        {
            current->next = new_node;
            current = new_node;
        }
    }

    node->t_cmd.args_size = ac - 1;
    node->t_cmd.redirections = NULL;
    node->t_cmd.flag_infiles = 0;
    node->t_cmd.flag_outfiles = 0;

    return node;
}

t_astnode *create_binary_node(node_type type, t_astnode *left, t_astnode *right) {
    t_astnode *node = (t_astnode *)gcalloc(sizeof(t_astnode));
    node->type = type;
    node->binary.left = left;
    node->binary.right = right;
    return node;
}

t_astnode *create_redirect_node(node_type type, t_astnode *child, char *filename) {
    t_astnode *node = (t_astnode *)gcalloc(sizeof(t_astnode));
    node->type = type;
    node->redirect.child = child;
    node->redirect.filename = strdup(filename);
    return node;
}
t_astnode *create_block_node(t_astnode *child) {
    t_astnode *node = (t_astnode *)gcalloc(sizeof(t_astnode));
    node->type = NODE_BLOCK;
    node->block.child = child;
    return node;
}

void print_redirection2(t_redir_list *redir_list, const char *type, int depth) {

    if (!redir_list) return;
    t_redir_list *current = redir_list;

    while (current) {
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
int there_is_quote(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '\'' || str[i] == '\"')
            return (1);
        i++;
    }
    return (0);
}
int write_heredoc_to_file(const char *delimiter, char *filename, t_lst *env)
{
    static int file_counter;
    char *expanded_line;

    sprintf(filename, "heredoc_file_%d", file_counter++);
    file_counter =1;
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Error opening file");
        return -1;
    }
    while (1)
    {
        char *line = readline("> ");
        if (!line)
        {
            close(fd);
            return -1;
        }
        printf("line is %s, delimiter is %s\n", line, delimiter);
        if (strcmp(line, delimiter) == 0)
        {
            break;
        }
        if(there_is_quote(delimiter))
        {
            expanded_line = line;
        }
        else
        {
         expanded_line = ft_expand_heredoc(line, env);
        }
        if (!expanded_line)
        {
            close(fd);
            return -1;
        }

        write(fd, expanded_line, strlen(expanded_line));
        write(fd, "\n", 1);  // Add newline
    }

    close(fd);
    return 0;
}

t_astnode *parse_cmd(t_tklist *tokens, t_lst *lst)
{
    t_token *token;
    int argc = 0;
    char *argv[100];  // Assuming max 100 args

    t_redir_list *redirections = NULL;

    // Handle redirections and command parsing
    while ((token = peek_token(tokens)) && 
           (token->type == TK_WORD || 
            token->type == TK_GREATERTHAN1 || token->type == TK_GREATERTHAN2 || 
            token->type == TK_LESSERTHAN2 || token->type == TK_LESSERTHAN1)) {
        
        if (token->type == TK_WORD) {
            token = next_token(tokens);
            argv[argc++] = token->value;
        } else {
            // Handle redirections
            t_redir *redir = gcalloc(sizeof(t_redir));
            if (!redir)
            {
                return NULL;
            }
            redir->file = NULL;
            redir->heredoc = NULL;

            if (token->type == TK_LESSERTHAN1)
            {
                redir->type = NODE_REDIRECT_IN;
            } else if (token->type == TK_LESSERTHAN2)
            {
                redir->type = NODE_HEREDOC;
            } else if (token->type == TK_GREATERTHAN1) {
                redir->type = NODE_REDIRECT_OUT;
            } else if (token->type == TK_GREATERTHAN2) {
                redir->type = NODE_REDIRECT_APPEND;
            }

            next_token(tokens); // Consume the redirection token
            token = next_token(tokens); // Get the filename token
            if (!token || token->type != TK_WORD) {
                // Handle error: expected filename after redirection operator
                return NULL;
            }

            redir->file = strdup(token->value);

            t_redir_list *redir_node = gcalloc(sizeof(t_redir_list));
            if (!redir_node) {
                return NULL;
            }
            redir_node->redir = redir;
            redir_node->next = NULL;

            ft_lstadd_back_redir(&redirections, redir_node);
        }
    }

    if (argc == 0 && !redirections) {
        return NULL;
    }

    t_astnode *cmd_node = create_ast_command(argc, argv);
    cmd_node->t_cmd.redirections = redirections;

    // Handle heredocs
    t_redir_list *current_heredoc = redirections;
    while (current_heredoc) {
        if (current_heredoc->redir->type == NODE_HEREDOC) {
            char *delimiter = current_heredoc->redir->file;

            // Generate a unique filename for the heredoc content
            char heredoc_file[50];
            if (write_heredoc_to_file(delimiter, heredoc_file, lst) != 0) {
                // Handle error in writing heredoc content
                return NULL;
            }

            // Store the generated filename in the redirection structure
            current_heredoc->redir->heredoc = strdup(heredoc_file);
            if (!current_heredoc->redir->heredoc)
            {
                // Handle memory allocation error
                return NULL;
            }
        }
        current_heredoc = current_heredoc->next;
    }

    return cmd_node;
}
t_astnode *parse_pipe(t_tklist *tokens, t_lst *lst)
{
    t_astnode *node1 = parse_cmd(tokens, lst);
    if (!node1) {
        printf("null in parse_pipe 1\n");

        return NULL;
    }

    t_token *token = peek_token(tokens);
    while (token && token->type == TK_PIPE) {
        next_token(tokens);
        t_astnode *node2 = parse_cmd(tokens, lst);
        if (!node2) {
        printf("null in parse_pipe 2\n");
            return NULL;
        }
        node1 = create_binary_node(NODE_PIPE, node1, node2);
        token = peek_token(tokens);
    }

    return node1;
}

t_astnode *parse_and_or(t_tklist *tokens, t_astnode *left, t_token *token, t_lst *lst) {
    t_astnode *node = NULL;
    t_astnode *right;

    if (token->type == TK_AND)
    {
        right = parse_pipe(tokens, lst);
        if (!right)
        {
            return NULL;
        }
        node = create_binary_node(NODE_LOGICAL_AND, left, right);
    }
    else if (token->type == TK_OR)
    {
        right = parse_pipe(tokens, lst);
        if (!right)
        {
            return NULL;
        }
        node = create_binary_node(NODE_LOGICAL_OR, left, right);
    }
    return node;
}
t_astnode *parse_command_line(t_tklist *tokens, t_lst *lst)
{
    t_astnode *node = parse_block(tokens, lst);
    
    if (!node) {
        printf("null in parse_command_line 1\n");
        return NULL;
    }

    t_token *token = peek_token(tokens);
    while (token && (token->type == TK_AND || token->type == TK_OR)) {
        token = next_token(tokens);
        t_astnode *right = parse_command_line(tokens, lst);
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

t_astnode *parse_block(t_tklist *tokens, t_lst *lst)
{
    t_token *token = peek_token(tokens);

    if (token && token->type == TK_LPR) {
        next_token(tokens);
        t_astnode *node = parse_command_line(tokens, lst);
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
        return parse_pipe(tokens, lst);
    }
}
