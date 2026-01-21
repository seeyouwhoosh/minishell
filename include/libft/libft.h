/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:57:02 by xwu               #+#    #+#             */
/*   Updated: 2026/01/21 13:10:36 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* Character identification */

int		ft_isalpha(int c);

int		ft_isdigit(int c);

int		ft_isalnum(int c);

int		ft_isprint(int c);

int		ft_isascii(int c);

int		ft_isspace(int c);

/* Character conversion */

int		ft_tolower(int c);

int		ft_toupper(int c);

/* Number and string conversion */

char	*ft_itoa(int n);

int		ft_atoi(const char *str);

double	ft_strtod(const char *restrict str, char **restrict endptr);

/* Outputting */

void	ft_putchar_fd(char c, int fd);

void	ft_putnbr_fd(int nb, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

/* Memory management */

void	*ft_memset(void *b, int c, size_t n);

void	ft_bzero(void *s, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

/* Changes the size of the memory block pointed by ptr to size bytes. If ptr
is NULL, is equivalent to malloc(size), if size is 0, is equivalent to
free(ptr)*/
void	*ft_realloc(void *ptr, size_t old_size, size_t size);

/* Strings */

size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* Locate a substring in a string. If str little is empty or is nowhere
in str big, returns NULL; else, return the pointer to the first
character to str little */
char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strdup(const char *s);

/* Allocates memory (using malloc(3)) and returns a substring from
the str s. The substring starts at index start and has a maximum
length of len */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* Allocates memory (using malloc(3)) and returns a new string, which
is the result of concatenating ’s1’ and ’s2’. */
char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strtrim(char const *s1, char const *set);

/* Allocates memory (using malloc(3)) and returns an array of strings
obtained by splitting ’s’ using the character ’c’ as a delimiter. The
array must end with a NULL pointer */
char	**ft_split(char const *s, char c);

char	**ft_split_charset(char const *s, const char *charset);

/* Special functions */

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* Linked lists */

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void*));

void	ft_lstclear(t_list **lst, void (*del)(void*));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Extra functions of lists not included in the subject */
void	del(void *content);

void	ft_freesplit(char **words);

/* Find number of words based on the separator c */
size_t	ft_strwords(const char *s, char c);

char	*ft_wordcpy(const char *s, size_t j, size_t i);

/* Dedicated putstr for split */
void	ft_putstrstr(char **s, char sep);

int		ft_strcmp(const char *s1, const char *s2);

#endif
