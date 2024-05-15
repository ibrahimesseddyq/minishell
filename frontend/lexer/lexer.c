#include "../frontend.h"
void	ft_lstadd_back(t_list **lst, t_list *new);

int is_delimiter(char c)
{
    if ( c == ' ')
	return (1);
	return (0);
}

t_token *gettoken(char *token)
{
	t_token *tk;

	tk = malloc(sizeof(t_token));
	if (*token == '|')
	{
		if(*(token + 1) == '|')
			return (tk->value = ft_strdup("||"), tk->type = TK_OR, tk);
		else
			return (tk->value = ft_strdup("|"), tk->type = TK_PIPE, tk);
	}
	else if(*token == ';')
		return (tk->value = ft_strdup( ";"), tk->type = TK_SEMICOLON, tk);
	else if(*token == '(')
		return (tk->value = ft_strdup( "("), tk->type = TK_LPR, tk);
	else if(*token == ')')
		return (tk->value = ft_strdup( ")"), tk->type = TK_RPR, tk);
	else if(*token == '>')
	{
		if(*(token + 1) == '>')
			return (tk->value = ft_strdup(">>"), tk->type = TK_GREATERTHAN2, tk);
		else
			return (tk->value = ft_strdup(">"), tk->type = TK_GREATERTHAN1, tk);
	}
	else if(*token == '<')
	{
		if(*(token + 1) == '<')
			return (tk->value = ft_strdup("<<"), tk->type = TK_LESSERTHAN2, tk);
		else
			return (tk->value = ft_strdup("<"), tk->type = TK_LESSERTHAN1, tk);
	}
	else if(*token == '&')
	{
		if (*(token + 1) == '&') {
			if (!(tk->value = ft_strdup("&&"))) {
				free(tk);
				return NULL;
			}
			tk->type = TK_AND2;
		} else {
			if (!(tk->value = ft_strdup("&"))) {
				free(tk);
				return NULL;
			}
			tk->type = TK_AND1;
		}
		return tk;
}
	else if(ft_isalnum(*token))
	{
		int len;
		int	i;
		char *str;

		len = ft_strlen(token);
		i = 0;
		str = (char *)malloc(sizeof(char) * len + 1);
		if (NULL == str)
			return (NULL);
		while(ft_isalnum(*token) && i < len)
		{
			str[i] = *token;
			i++;
			token++;
		}
		str[i] = '\0';
		if(len != i)
			return (free(str), tk->type = TK_ILLEGAL, tk);
		else
			return  (tk->type = TK_COMMAND, tk->value = str, tk);
		
	}
	else
		return (tk->type=TK_ILLEGAL, tk);
}
t_list *lex(char *text)
{
	// printf("[%s]",text);
    t_list *tk_list = NULL;
    int start = 0;
    int i = 0;

    while (text[i])
	{
        if (
			is_delimiter(text[i]) ||
			 text[i+1] == '\0')
		{
            int length = (text[i+1] == '\0' && !is_delimiter(text[i])) ? i + 1 - start : i - start;
            if (length > 0)
			{
                char *value = ft_substr(text, start, length);
                t_token *token = gettoken(value);
                free(value);
                if (token)
				{
                    ft_lstadd_back(&tk_list, ft_lstnew(token));
                }
            }
            start = i + 1; 
        }
        i++;
    }

    return tk_list;
}
int check_double(char *str)
{
        if ((str[0] == '>' && str[1] == '>') ||
            (str[0] == '<' && str[1] == '<') ||
            (str[0] == '|' && str[1] == '|') ||
			(str[0] == '&' && str[1] == '&') ||
            (str[0] == '$' && str[1] == '$') ||
			(str[0] == '.' && str[1] == '.') 
			)
			return (1);
		return (0);
}
int issymbol(char c)
{
        if (c == '>' || c == '<' || c == '|' || c == '&' || c == '$' || c == '.' || c == '(' || c == ')')
			return (1);
		return (0);
}
char *add_spaces( char *str)
{
    int len = strlen(str);
    char *max_str = malloc(sizeof(char) * (len * 3) + 1);
    if (!max_str) return NULL;

    int i = 0, j = 0;
    while (i < len) {
        if (check_double(str + i))
			 {
            if (j > 0 && max_str[j-1] != ' ') max_str[j++] = ' ';
            max_str[j++] = str[i];
            max_str[j++] = str[i++];
            i++; 
            max_str[j++] = ' ';
        }
		else if (issymbol(str[i]))
		{
            if (j > 0 && max_str[j-1] != ' ') max_str[j++] = ' ';
            max_str[j++] = str[i++];
            max_str[j++] = ' ';
        }
		else if (ft_isalnum(str[i]))
		{
            if (j > 0 && max_str[j-1] == ' ') max_str[j++] = ' '; 
            while (ft_isalnum(str[i])) {
                max_str[j++] = str[i++];
            }
        }
		else
		{
            max_str[j++] = str[i++];
        }
    }
    max_str[j] = '\0';
    return max_str;
}
