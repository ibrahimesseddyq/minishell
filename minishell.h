#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h" 
#include <readline/readline.h>
#include <readline/history.h>

char	*get_next_line(int fd);
#endif