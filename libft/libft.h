/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynachat <ynachat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:42:23 by ibes-sed          #+#    #+#             */
/*   Updated: 2024/10/22 20:10:17 by ynachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>

# define DEFAULT_NB 600

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_list_string
{
	char			*content;
	struct s_list	*next;
}	t_list_string;

typedef struct s_lst
{
	char			*key;
	char			signe;
	char			*value;
	int				set;
	int				will_split;
	struct s_lst	*next;
}	t_lst;

typedef struct s_redir
{
	char	*file;
	char	*heredoc;
	int		type;
	int		number;
}	t_redir;

typedef struct s_redir_list
{
	t_redir				*redir;
	struct s_redir_list	*next;
}	t_redir_list;

typedef struct s_fdnode
{
	int					fd;
	int					in_use;
	struct s_fdnode		*next;
}	t_fdnode;

typedef struct s_split_quotes
{
	int		i;
	int		index;
	int		word_length;
	char	**arr;
	int		in_single_quote;
	int		in_double_quote;
	int		tail_matrice;
}	t_split_quotes;

typedef struct s_count_word
{
	int	i;
	int	cnt;
	int	in_single_quote;
	int	in_double_quote;
}	t_count_word;

typedef struct s_export_var
{
	int		exist;
	int		append_mode;
	char	*key;
	char	*value;
	char	*temp;
	int		will_split;
}	t_export_var;

int				ft_atoi(const char *str);

void			ft_bzero(void *s, size_t n);

void			*ft_calloc(size_t count, size_t size);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

char			*ft_itoa(int n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			*ft_memset(void *str, int c, size_t n);

void			ft_putchar_fd(char c, int fd);

void			ft_putendl_fd(char *s, int fd);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr_fd(char *s, int fd);

char			**ft_split(char const *s, char c);

char			*ft_strchr(const char *s, int c);

char			*ft_strdup(char *src);

void			ft_striteri(char *s, void (*f)(unsigned int, char*));

char			*ft_strjoin(char *s1, char *s2);

size_t			ft_strlcat(char *dest, const char *src, unsigned int size);

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t			ft_strlen(const char *str);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_strncmp(const char *s1, const char *s2, unsigned int n);

char			*ft_strnstr(const char *str, const char *to_find, size_t len);

char			*ft_strrchr(const char *s, int c);

char			*ft_strtrim(char const *s1, char const *set);

char			*ft_substr(char const *s, unsigned int start, size_t len);

int				ft_tolower(int c);

int				ft_toupper(int c);

t_list			*ft_lstnew(void *content);

void			ft_lstadd_front(t_list **lst, t_list *new);

int				ft_lstsize(t_list *lst);

t_list			*ft_lstlast(t_list *lst);

void			ft_lstadd_back(t_list **lst, t_list *new);

void			ft_lstdelone(t_list *lst, void (*del)(void*));

void			ft_lstclear(t_list **lst, void (*del)(void*));

void			ft_lstiter(t_list *lst, void (*f)(void *));

t_lst			*ft_lstadd_new_env(char *key, char *value, char singe);

void			ft_lstadd_back_env(t_lst **lst, t_lst *new);

void			ft_lst_clear_env(t_lst **lst);

int				ft_strcmp(char *s1, char *s2);

void			ft_lstadd_back_redir(t_redir_list **lst, t_redir_list *new);

void			*gcalloc(size_t size);

void			*ft_realloc(void *ptr,
					unsigned int old_size, unsigned int new_size);

void			clean_fd(void);

int				ft_close(int *fd);

char			*ft_getcwd(char *buf, size_t size);

pid_t			ft_fork(void);

__int128		ft_atoi128(const char *str);

char			*ft_strncpy(char *dest, char *src, unsigned int n);

char			*ft_strtok(char *str, const char *sepa);

#endif