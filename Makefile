SRC_LEXER = main.c ./frontend/lexer/lexer.c
OBJ_LEXER = $(SRC_LEXER:.c=.o)

LIBFT = libft.a
LIBFT_SRC = $(wildcard ./libft/*.c) # This wildcard is used correctly
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

SRC = ./frontend/lexer/lexer.c ./frontend/parser/parser.c ./frontend/parser/syntax_analyzer.c ./frontend/parser/parser_printer.c \
			exec/exec_cmd_line.c exec/exec_cmd.c exec/exec_pip.c exec/exec_or.c exec/exec_and.c
OBJ = $(SRC:.c=.o)

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

all: lexer parser

$(LIBFT): $(LIBFT_OBJ)
	ar rc $(LIBFT) $(LIBFT_OBJ)
	ranlib $(LIBFT)

$(LIBFT_OBJ): ./libft/%.o: ./libft/%.c
	$(CC) $(CFLAGS) -c $< -o $@

lexer: $(OBJ_LEXER) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LEXER) $(LIBFT)

minishell : $(OBJ) $(LIBFT) main.c
	$(CC) $(CFLAGS) main.c -o $@ $(OBJ) $(LIBFT)  -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ_LEXER) $(LIBFT_OBJ) $(LIBFT) lexer parser $(OBJ)
re: clean minishell

.PHONY: all clean
