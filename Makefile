NAME= minishell
LIB = -L/Users/ibes-sed/.brew/opt/readline/lib
INCLUDE = -I/Users/ibes-sed/.brew/opt/readline/include
SRC_LEXER = main.c ./parsing/lexer/lexer.c
OBJ_LEXER = $(SRC_LEXER:.c=.o)
LIBFT = libft.a
LIBFT_SRC = $(wildcard ./libft/*.c)
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
SRC = main_utils.c ./redirection/redir_in_utils.c ./parsing/lexer/lexer.c ./parsing/parser/parser.c ./parsing/parser/ft_sprintf.c ./parsing/parser/heredoc_files.c ./parsing/parser/parser_utils1.c ./parsing/parser/parser_utils2.c ./parsing/parser/parser_utils3.c ./parsing/lexer/lexer_utils1.c ./parsing/lexer/lexer_utils2.c ./parsing/lexer/lexer_utils3.c ./parsing/lexer/lexer_utils4.c ./parsing/parser/syntax_analyzer.c ./parsing/parser/parser_printer.c \
 exec/exec_cmd_line.c exec/exec_cmd.c exec/exec_pip.c exec/exec_or.c exec/exec_and.c env/envp.c backend/wild_card.c \
 exporting/get_env.c exporting/set_env.c redirection/ft_red_in.c redirection/ft_red_out.c redirection/ft_redirection.c expanding/expand_normal.c expanding/expand_redir.c expanding/expand_delimiter.c expanding/expand_heredoc.c ./builtins/cd.c ./builtins/pwd.c ./backend/exit_status.c ./builtins/echo.c ./builtins/unset.c ./builtins/env.c ./builtins/exit.c ./backend/gc/gcalloc.c exec/split_ai.c exec/split_utils.c exec/exec_cmd_utils.c exec/split_utils2.c exec/exec_cmd2.c exec/exec_cmd3.c exec/exec_cmd4.c exec/exec_cmd5.c exec/exec_cmd6.c exec/exec_cmd7.c expanding/expand_utils1.c expanding/expand_utils2.c exporting/env_utils1.c exporting/env_utils2.c	
OBJ = $(SRC:.c=.o)
CC = cc -g
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(LIBFT): $(LIBFT_OBJ)
	ar rc $(LIBFT) $(LIBFT_OBJ)
	ranlib $(LIBFT)

$(LIBFT_OBJ): ./libft/%.o: ./libft/%.c
	$(CC) $(CFLAGS) -c $< -o $@

lexer: $(OBJ_LEXER) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LEXER) $(LIBFT)

minishell: $(OBJ) $(LIBFT) main.c
	$(CC) $(CFLAGS) main.c $(OBJ) -o $@ $(LIB) $(INCLUDE) -lreadline $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJ_LEXER) $(LIBFT_OBJ) $(LIBFT) lexer minishell $(OBJ)

re: clean minishell
