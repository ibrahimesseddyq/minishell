#include "../frontend.h"
#define WORD ".[]\\-_\"\'&$/"

t_lexer* init_lexer(char *input) {
    t_lexer *lexer = (t_lexer *)malloc(sizeof(t_lexer));
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
    while (lexer->currentchar != '\0' && isspace(lexer->currentchar)) {
        advance(lexer);
    }
}

char* get_word(t_lexer *lexer)
{
    char *result = (char *)malloc(256 * sizeof(char));
    int i = 0;
    int in_quotes = 0;

    // printf("befor the while\n");
    while (lexer->currentchar != '\0' && 
           (in_quotes || (!isspace(lexer->currentchar) && 
                           lexer->currentchar != '|' && 
                           lexer->currentchar != '&' && 
                           lexer->currentchar != ';' && 
                           lexer->currentchar != '(' && 
                           lexer->currentchar != ')' && 
                           lexer->currentchar != '>' && 
                           lexer->currentchar != '<'))) {
        if (lexer->currentchar == '"') {
            in_quotes = !in_quotes;
        }
        result[i++] = lexer->currentchar;
        advance(lexer);
    }
    // printf("after the while\n");

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
                token->value = ft_strdup("||");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_PIPE;
            token->value = ft_strdup("|");
            return token;
        }

        if (lexer->currentchar == '&') {
            advance(lexer);
            if (lexer->currentchar == '&') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_AND;
                token->value = ft_strdup("&&");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_ILLEGAL;
            token->value = ft_strdup("");
            return token;
        }

        if (lexer->currentchar == ';') {
            advance(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_SEMICOLON;
            token->value = ft_strdup(";");
            return token;
        }

        if (lexer->currentchar == '(') {
            advance(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_LPR;
            token->value = ft_strdup("(");
            return token;
        }

        if (lexer->currentchar == ')') {
            advance(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_RPR;
            token->value = ft_strdup(")");
            return token;
        }

        if (lexer->currentchar == '>') {
            advance(lexer);
            if (lexer->currentchar == '>') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_GREATERTHAN2;
                token->value = ft_strdup(">>");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_GREATERTHAN1;
            token->value = ft_strdup(">");
            return token;
        }

        if (lexer->currentchar == '<') {
            advance(lexer);
            if (lexer->currentchar == '<') {
                advance(lexer);
                t_token *token = (t_token *)malloc(sizeof(t_token));
                token->type = TK_LESSERTHAN2;
                token->value = ft_strdup("<<");
                return token;
            }
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_LESSERTHAN1;
            token->value = ft_strdup("<");
            return token;
        }

        if (ft_isalnum(lexer->currentchar) || ft_strchr(WORD,lexer->currentchar))
        {
            char *word = get_word(lexer);
            t_token *token = (t_token *)malloc(sizeof(t_token));
            token->type = TK_WORD;
            token->value = word;
            return token;
        }

        t_token *token = (t_token *)malloc(sizeof(t_token));
        token->type = TK_ILLEGAL;
        token->value = ft_strdup("");
        return token;
    }

    t_token *token = (t_token *)malloc(sizeof(t_token));
    token->type = TOKEN_EOF;
    token->value = strdup("EOF");
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

    // Add the final TOKEN_EOF to the list
    token_list->size++;
    token_list->tokens = (t_token *)realloc(token_list->tokens, token_list->size * sizeof(t_token));
    token_list->tokens[token_list->size - 1] = *token;

    // Free the lexer
    free(token);
    free(lexer);

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