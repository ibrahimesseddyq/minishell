#include "../frontend.h"
#define WORD ".[]\\-_\"\'&$/*"
#define INITIAL_BUFFER_SIZE 256
#define BUFFER_GROWTH_FACTOR 2
t_lexer* init_lexer(char *input) {
    t_lexer *lexer = (t_lexer *)gcalloc(sizeof(t_lexer));
    lexer->input = input;
    lexer->pos = 0;
    lexer->currentchar = input[lexer->pos];
    return lexer;
}

void advance(t_lexer *lexer) {
    lexer->pos++;
    if (lexer->pos >= (int)ft_strlen(lexer->input)) {
        lexer->currentchar = '\0';
    } else {
        lexer->currentchar = lexer->input[lexer->pos];
    }
}

void skip_whitespace(t_lexer *lexer) {
    while (lexer->currentchar != '\0' && (isspace(lexer->currentchar) || lexer->currentchar == '\n')) {
        advance(lexer);
    }
}

char* get_word(t_lexer *lexer)
{
    size_t buffer_size = INITIAL_BUFFER_SIZE;
    char *result = (char *)gcalloc(buffer_size * sizeof(char));
    if (!result) return NULL;

    size_t i = 0;
    int in_quotes = 0;
    char quote_char = '\0';

    while (lexer->currentchar != '\0') {
        // Check if we need to resize the buffer
        if (i >= buffer_size - 1) {
            buffer_size *= BUFFER_GROWTH_FACTOR;
            char *new_result = (char *)realloc(result, buffer_size * sizeof(char));
            if (!new_result) {
                // Handle memory allocation failure
                return result;
            }
            result = new_result;
        }

        if (!in_quotes && (lexer->currentchar == '"' || lexer->currentchar == '\'')) {
            in_quotes = 1;
            quote_char = lexer->currentchar;
            result[i++] = lexer->currentchar;
            advance(lexer);
        } else if (in_quotes && lexer->currentchar == quote_char) {
            in_quotes = 0;
            result[i++] = lexer->currentchar;
            advance(lexer);
            if (lexer->currentchar == '\0' || isspace(lexer->currentchar) ||
                lexer->currentchar == '|' || lexer->currentchar == '&' ||
                lexer->currentchar == ';' || lexer->currentchar == '(' ||
                lexer->currentchar == ')' || lexer->currentchar == '>' ||
                lexer->currentchar == '<') {
                break;
            }
        } else if (lexer->currentchar == '\\') {
            // Handle escaped characters
            result[i++] = lexer->currentchar;  // Add the backslash
            advance(lexer);
            if (lexer->currentchar != '\0') {
                result[i++] = lexer->currentchar;  // Add the escaped character
                advance(lexer);
            }
        } else if (!in_quotes && (isspace(lexer->currentchar) ||
                   lexer->currentchar == '|' || lexer->currentchar == '&' ||
                   lexer->currentchar == ';' || lexer->currentchar == '(' ||
                   lexer->currentchar == ')' || lexer->currentchar == '>' ||
                   lexer->currentchar == '<')) {
            break;
        } else {
            result[i++] = lexer->currentchar;
            advance(lexer);
        }
    }

    result[i] = '\0';

    // Trim the buffer to the actual size used
    char *final_result = (char *)realloc(result, (i + 1) * sizeof(char));
    return final_result ? final_result : result;
}

t_token* get_next_token(t_lexer *lexer) {
    printf("current char is [%c]\n", lexer->currentchar);
    while (lexer->currentchar != '\0') {
        if (isspace(lexer->currentchar) || lexer->currentchar == '\n') {
            skip_whitespace(lexer);
            continue;
        }

        if (lexer->currentchar == '|') {
            advance(lexer);
            if (lexer->currentchar == '|') {
                advance(lexer);
                t_token *token = (t_token *)gcalloc(sizeof(t_token));
                token->type = TK_OR;
                token->value = ft_strdup("||");
                return token;
            }
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_PIPE;
            token->value = ft_strdup("|");
            return token;
        }

        if (lexer->currentchar == '&') {
            advance(lexer);
            if (lexer->currentchar == '&') {
                advance(lexer);
                t_token *token = (t_token *)gcalloc(sizeof(t_token));
                token->type = TK_AND;
                token->value = ft_strdup("&&");
                return token;
            }
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_ILLEGAL;
            token->value = ft_strdup("");
            return token;
        }

        if (lexer->currentchar == ';') {
            advance(lexer);
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_SEMICOLON;
            token->value = ft_strdup(";");
            return token;
        }

        if (lexer->currentchar == '(') {
            advance(lexer);
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_LPR;
            token->value = ft_strdup("(");
            return token;
        }

        if (lexer->currentchar == ')') {
            advance(lexer);
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_RPR;
            token->value = ft_strdup(")");
            return token;
        }

        if (lexer->currentchar == '>') {
            advance(lexer);
            if (lexer->currentchar == '>') {
                advance(lexer);
                t_token *token = (t_token *)gcalloc(sizeof(t_token));
                token->type = TK_GREATERTHAN2;
                token->value = ft_strdup(">>");
                return token;
            }
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_GREATERTHAN1;
            token->value = ft_strdup(">");

            return token;
        }

        if (lexer->currentchar == '<') {
            advance(lexer);
            if (lexer->currentchar == '<') {
                advance(lexer);
                t_token *token = (t_token *)gcalloc(sizeof(t_token));
                token->type = TK_LESSERTHAN2;
                token->value = ft_strdup("<<");
                return token;
            }
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_LESSERTHAN1;
            token->value = ft_strdup("<");
            return token;
        }

        if (ft_isalnum(lexer->currentchar) || ft_strchr(WORD,lexer->currentchar))
        {
            char *word = get_word(lexer);
            t_token *token = (t_token *)gcalloc(sizeof(t_token));
            token->type = TK_WORD;
            token->value = word;
            return token;
        }
        char unrecognized[2] = {lexer->currentchar, '\0'};
        advance(lexer);  // Add this line to move past the unrecognized character
        t_token *token = (t_token *)gcalloc(sizeof(t_token));
        token->type = TK_ILLEGAL;
        token->value = ft_strdup(unrecognized);
        return token;
    }

    t_token *token = (t_token *)gcalloc(sizeof(t_token));
    token->type = TOKEN_EOF;
    token->value = strdup("EOF");
    return token;
}

t_tklist* tokenize(char *input)
{
    t_lexer *lexer = init_lexer(input);
    t_tklist *token_list = (t_tklist *)gcalloc(sizeof(t_tklist));
    token_list->tokens = NULL;
    token_list->curr_index = 0;
    token_list->size = 0;
    t_token *token = get_next_token(lexer);
    while (token->type != TOKEN_EOF)
    {
        token_list->size++;
        printf("size is %d and token is %s\n", token_list->size, token->value);
        token_list->tokens = (t_token *)realloc(token_list->tokens, token_list->size * sizeof(t_token));
        token_list->tokens[token_list->size - 1] = *token;
        token = get_next_token(lexer);
    }

    // Add the final TOKEN_EOF to the list
    token_list->size++;
    token_list->tokens = (t_token *)realloc(token_list->tokens, token_list->size * sizeof(t_token));
    token_list->tokens[token_list->size - 1] = *token;


    return token_list;
}

t_token* peek_token(t_tklist *token_list) {
    if (token_list->curr_index < token_list->size) {
        return &token_list->tokens[token_list->curr_index];
    }
    return NULL;
}

t_token* next_token(t_tklist *token_list) {
    if (token_list->curr_index < token_list->size) {
        return &token_list->tokens[token_list->curr_index++];
    }
    return NULL;
}

void set_beginning(t_tklist *token_list)
{
    token_list->curr_index = 0;
}

t_token* peek_next_token(t_tklist *token_list, int offset) {
    if ((token_list->curr_index + offset) < token_list->size) {
        return &token_list->tokens[token_list->curr_index + offset];
    }
    return NULL;
}