CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c ft_lstadd_new_env.c ft_lstadd_back_env.c ft_lst_clear_env.c ft_strcmp.c ft_realloc.c fd.c ft_fork.c ft_getcwd.c ft_strncpy.c

SRCS_BONNUS = ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstlast_bonus.c ft_lstiter_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c

OBJECTS = $(SRCS:.c=.o)

OBJECTS_BONNUS = $(SRCS_BONNUS:.c=.o)

RM = rm -f

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	ar cr $(NAME) $(OBJECTS) && $(MAKE) clean

bonus: $(OBJECTS_BONNUS)
	ar cr $(NAME) $(OBJECTS_BONNUS)

clean:
	$(RM) $(OBJECTS) $(OBJECTS_BONNUS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)
