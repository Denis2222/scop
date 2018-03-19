/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:35:10 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/15 20:00:33 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "argvise.h"

int					ft_abs(int n);
size_t				ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
int					ft_strcmp(char *s1, const char *s2);
int					ft_strncmp(char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isblank(int c);
int					ft_isspace(int c);
char				*ft_strrev(char *str);
char				*ft_strstr(char *str, const char *to_find);
char				*ft_strnstr(const char *str, const char *to_find, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t nb);
size_t				ft_strlcat(char *dest, const char *src, size_t nb);
char				*ft_strrepchr(char *str, char c, char n);
char				*ft_strdup(char *src);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strchr(const char *s, int c);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strtolower(char *str);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(int nbr);
void				ft_putptr(void *ptr);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				*ft_strtrimfree(char *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putulongnbr_fd(unsigned long nbr, int fd);
void				ft_putulongnbr(unsigned long nbr);

int					ft_sqrt(int nb);
long				ft_pow(int nb, int e);
int					ft_tablen(char **tab);
void				ft_tabfree(char **tab);
char				*ft_strrepchrbystr(char *str, char c, char *rep);
int					ft_streachr(char *str, int(f)(int));
int					ft_strcountchr(char *str, char chr);

#endif
