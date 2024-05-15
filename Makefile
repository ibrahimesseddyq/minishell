# Variables
SRC_LEXER = main.c ./frontend/lexer/lexer.c ./frontend/lexer/lexer_tester.c
OBJ_LEXER = $(SRC_LEXER:.c=.o)  # Pattern substitution to replace .c with .o
LIBFT = libft.a
LIBFT_SRC = $(wildcard ./libft/*.c)  # Correct wildcard usage
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

# Default target
all: lexer

# Static library for libft
$(LIBFT): $(LIBFT_OBJ)
	ar rc $(LIBFT) $(LIBFT_OBJ)
	ranlib $(LIBFT)  # Ensure the library index is updated

# Compile libft source files into object files
$(LIBFT_OBJ): %.o: %.c
	gcc -c $< -o $@
# Lexer executable
lexer: $(OBJ_LEXER) $(LIBFT)
	gcc -o $@ $(OBJ_LEXER) $(LIBFT)  # Ensure linking of all necessary object files and libraries

# Generic rule for compiling source files to object files
%.o: %.c
	gcc -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_LEXER) $(LIBFT_OBJ) $(LIBFT) lexer

# Phony targets
.PHONY: all clean
