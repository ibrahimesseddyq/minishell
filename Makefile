NAME = minishell
HEADER = minishell.h
LIBFT_HEADER = ./libft/libft.h
LIB = -L/Users/ibes-sed/.brew/opt/readline/lib
INCLUDE = -I/Users/ibes-sed/.brew/opt/readline/include
SRC_LEXER = main.c ./parsing/lexer/lexer.c
OBJ_LEXER = $(SRC_LEXER:.c=.o)
LIBFT = libft.a
LIBFT_SRC = ./libft/fd.c ./libft/ft_atoi.c ./libft/ft_atoi128.c ./libft/ft_bzero.c ./libft/ft_calloc.c ./libft/ft_fork.c ./libft/ft_getcwd.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c ./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_itoa.c ./libft/ft_lst_clear_env.c ./libft/ft_lstadd_back_bonus.c ./libft/ft_lstadd_back_redir.c ./libft/ft_lstadd_front_bonus.c ./libft/ft_lstadd_new_env.c ./libft/ft_lstclear_bonus.c ./libft/ft_lstdelone_bonus.c ./libft/ft_lstiter_bonus.c ./libft/ft_lstlast_bonus.c ./libft/ft_lstnew_bonus.c ./libft/ft_lstsize_bonus.c ./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putstr_fd.c ./libft/ft_realloc.c ./libft/ft_split_quotes.c ./libft/ft_split.c ./libft/ft_strchr.c ./libft/ft_strcmp.c ./libft/ft_striteri.c ./libft/ft_strjoin.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strmapi.c ./libft/ft_strncmp.c ./libft/ft_strncpy.c ./libft/ft_strnstr.c ./libft/ft_strrchr.c ./libft/ft_strtok.c ./libft/ft_strtrim.c ./libft/ft_substr.c ./libft/ft_tolower.c ./libft/ft_toupper.c ./libft/ft_strdup.c ./libft/ft_putnbr_fd.c ./libft/ft_lstadd_back_env.c
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
SRC = main_utils.c ./redirection/redir_in_utils.c ./redirection/redir_utils.c ./parsing/lexer/lexer.c ./parsing/parser/parser.c ./parsing/parser/ft_sprintf.c ./parsing/parser/heredoc_files.c ./parsing/parser/parser_utils1.c ./parsing/parser/parser_utils2.c ./parsing/parser/parser_utils4.c ./parsing/parser/parser_utils3.c ./parsing/lexer/lexer_utils1.c ./parsing/lexer/lexer_utils2.c ./parsing/lexer/lexer_utils3.c ./parsing/lexer/lexer_utils4.c ./parsing/lexer/lexer_utils5.c ./parsing/parser/syntax_analyzer.c ./parsing/parser/syntax_analyzer_utils.c \
 exec/exec_cmd_line.c exec/exec_cmd.c exec/exec_pip.c exec/exec_or.c exec/exec_and.c envr/envp.c extra/wild_card.c extra/wild_card2.c \
 exporting/get_env.c exporting/set_env.c redirection/ft_red_in.c redirection/ft_red_out.c redirection/ft_redirection.c expanding/expand_normal.c expanding/expand_redir.c expanding/expand_delimiter.c expanding/expand_heredoc.c ./builtins/cd.c ./builtins/cd_utils.c ./builtins/pwd.c ./extra/exit_status.c ./extra/wildcard_utils.c ./extra/wildcard_utils2.c ./builtins/echo.c ./builtins/unset.c ./builtins/env.c ./builtins/exit.c ./extra/gc/gcalloc.c exec/split_ai.c exec/split_utils.c exec/exec_cmd_utils.c exec/split_utils2.c exec/exec_cmd2.c exec/exec_cmd3.c exec/exec_cmd4.c exec/exec_cmd5.c exec/exec_cmd6.c exec/exec_cmd7.c exec/exec_wildcard.c exec/exec_cmd8.c exec/exec_cmd9.c exec/exec_cmd10.c expanding/expand_utils1.c expanding/expand_utils2.c expanding/expand_utils3.c expanding/expand_utils4.c exporting/env_utils1.c exporting/env_utils2.c exporting/env_utils3.c
OBJ = $(SRC:.c=.o)
MAIN_OBJ = main.o
CC = cc 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN_OBJ) -o $@ $(LIB) $(INCLUDE) -lreadline $(LIBFT)

$(LIBFT): $(LIBFT_OBJ)
	ar rc $(LIBFT) $(LIBFT_OBJ)

$(LIBFT_OBJ): ./libft/%.o: ./libft/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): main.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

lexer: $(OBJ_LEXER) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LEXER) $(LIBFT)

clean:
	rm -f $(OBJ_LEXER) $(LIBFT_OBJ) $(LIBFT) lexer $(OBJ) $(MAIN_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
