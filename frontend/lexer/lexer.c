#include "../frontend.h"

t_lexer* init_lexer(char *input) {
    t_lexer *lexer = (t_lexer *)malloc(sizeof(t_lexer));
    lexer->input = input;
    lexer->pos = 0;
    lexer->currentchar = input[lexer->pos];
    return lexer;
}

void advance(t_lexer *lexer) {
    lexer->pos++;
    if (lexer->pos >= strlen(lexer->input)) {
        lexer->currentchar = '\0';
    } else {
        lexer->currentchar = lexer->input[lexer->pos];
    }
}

void skip_whitespace(t_lexer *lexer) {
    while (lexer->currentchar != '\0' && isspace(lexer->currentchar)) {
        advance(lexer);
    }
}

char* get_word(t_lexer *lexer) {
    char *result = (char *)malloc(256 * sizeof(char));
    int i = 0;
    while (lexer->currentchar != '\0' && !isspace(lexer->currentchar) && lexer->currentchar != '|' && lexer->currentchar != '&' && lexer->currentchar != ';' && lexer->currentchar != '(' && lexer->currentchar != ')' && lexer->currentchar != '>' && lexer->currentchar != '<') {
        result[i++] = lexer->currentchar;
        advance(lexer);
    }
    result[i] = '\0';
    return result;
}

t_token* get_next_token(t_lexer *lexer) {
    while (lexer->currentchar != '\0') {
        if (isspace(lexer->currentchar)) {
            skip_whitespace(lexer);
            continue;
        }

        if (lexer->currentchar == '|') {
            advance(lexer);
            if (lexer->currentchar == '|') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_OR;
                token->value = strdup("||");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_PIPE;
            token->value = strdup("|");
            return token;
        }

        if (lexer->currentchar == '&') {
            advance(lexer);
            if (lexer->currentchar == '&') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_AND2;
                token->value = strdup("&&");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_AND1;
            token->value = strdup("&");
            return token;
        }

        if (lexer->currentchar == ';') {
            advance(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_SEMICOLON;
            token->value = strdup(";");
            return token;
        }

        if (lexer->currentchar == '(') {
            advance(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_LPR;
            token->value = strdup("(");
            return token;
        }

        if (lexer->currentchar == ')') {
            advance(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_RPR;
            token->value = strdup(")");
            return token;
        }

        if (lexer->currentchar == '>') {
            advance(lexer);
            if (lexer->currentchar == '>') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_GREATERTHAN2;
                token->value = strdup(">>");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_GREATERTHAN1;
            token->value = strdup(">");
            return token;
        }

        if (lexer->currentchar == '<') {
            advance(lexer);
            if (lexer->currentchar == '<') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_LESSERTHAN2;
                token->value = strdup("<<");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_LESSERTHAN1;
            token->value = strdup("<");
            return token;
        }

        if (isalnum(lexer->currentchar)) {
            char *word = get_word(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_WORD;
            token->value = word;
            return token;
        }

        t_token *token = (t_token *)malloc(sizeof(t_token));
        token->type = TK_ILLEGAL;
        token->value = strdup("");
        return token;
    }

    t_token *token = (t_token *)malloc(sizeof(t_token));
    token->type = TOKEN_EOF;
    token->value = strdup("");
    return token;
}

t_tklist* tokenize(char *input)
{
    t_lexer *lexer = init_lexer(input);
    t_tklist *token_list = (t_tklist *)malloc(sizeof(t_tklist));
    token_list->tokens = NULL;
    token_list->curr_index = 0;
    token_list->size = 0;

    t_token *token = get_next_token(lexer);
    while (token->type != TOKEN_EOF) {
        token_list->size++;
        token_list->tokens = (t_token *)realloc(token_list->tokens, token_list->size * sizeof(t_token));
        token_list->tokens[token_list->size - 1] = *token;
        token = get_next_token(lexer);
    }

    free(lexer);
    return token_list;
}

void print_tokens(t_tklist *token_list)
{
    for (int i = 0; i < token_list->size; i++) {
        printf("Type: %d, Value: %s\n", token_list->tokens[i].type, token_list->tokens[i].value);
    }
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

t_token* peek_next_token(t_tklist *token_list, int offset) {
    if ((token_list->curr_index + offset) < token_list->size) {
        return &token_list->tokens[token_list->curr_index + offset];
    }
    return NULL;
}
