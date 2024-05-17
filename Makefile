SRC_LEXER = main.c ./frontend/lexer/lexer.c ./frontend/lexer/lexer_tester.c
OBJ_LEXER = $(SRC_LEXER:.c=.o)  

LIBFT = libft.a
LIBFT_SRC = $(wildcard ./libft/*.c) # This wildcard is used correctly
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

SRC = main.c ./frontend/lexer/lexer.c ./frontend/lexer/lexer_tester.c ./frontend/parser/parser.c ./frontend/parser/parser_printer.c
OBJ = $(SRC:.c=.o)  

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

all: lexer parser

$(LIBFT): $(LIBFT_OBJ)
	ar rc $(LIBFT) $(LIBFT_OBJ)
	ranlib $(LIBFT)

$(LIBFT_OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

lexer: $(OBJ_LEXER) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LEXER) $(LIBFT)

parser: $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_LEXER) $(LIBFT_OBJ) $(LIBFT) lexer parser $(OBJ)

# Phony 
.PHONY: all clean
