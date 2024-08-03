

LIB = -L/Users/ibes-sed/.brew/opt/readline/lib
INCLUDE = -I/Users/ibes-sed/.brew/opt/readline/include


SRC_LEXER = main.c ./frontend/lexer/lexer.c
OBJ_LEXER = $(SRC_LEXER:.c=.o)

LIBFT = libft.a
LIBFT_SRC = $(wildcard ./libft/*.c)
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

SRC = ./frontend/lexer/lexer.c ./frontend/parser/parser.c ./frontend/parser/syntax_analyzer.c ./frontend/parser/parser_printer.c \
			exec/exec_cmd_line.c exec/exec_cmd.c exec/exec_pip.c exec/exec_or.c exec/exec_and.c env/envp.c  \
			export/get_env.c export/set_env.c redirection/ft_red_in.c redirection/ft_red_out.c redirection/ft_redirection.c expanding/test_expand.c ./builtins/cd.c ./builtins/pwd.c ./backend/exit_status.c
OBJ = $(SRC:.c=.o)

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
all: lexer parser

$(LIBFT): $(LIBFT_OBJ)
	ar rc $(LIBFT) $(LIBFT_OBJ)
	ranlib $(LIBFT)

$(LIBFT_OBJ): ./libft/%.o: ./libft/%.c
	$(CC) $(CFLAGS) -c $< -o $@

lexer: $(OBJ_LEXER) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LEXER) $(LIBFT)

minishell : $(OBJ) $(LIBFT) main.c
	$(CC) -lreadline $(CFLAGS) main.c  $(LIB) $(LIBFT) -o $@ $(OBJ)   
	#  -L /Users/ibes-sed/.brew/opt/readline/lib/libreadline.a -lreadline

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJ_LEXER) $(LIBFT_OBJ) $(LIBFT) lexer parser $(OBJ)
re: clean minishell

.PHONY: all clean
