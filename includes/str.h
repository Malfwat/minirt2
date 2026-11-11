/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:27:06 by me                #+#    #+#             */
/*   Updated: 2026/11/11 18:41:44 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>
# include <stdbool.h>
# include <math.h>

/* ft_strchr.c */
char	*ft_strchr(const char *s, char c);

/* ft_strcmp.c */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* ft_strlen.c */
size_t	ft_strlen(const char *str);

/* ft_strdup.c */
char	*ft_strdup(const char *str);
// char	*ft_strdup_range(const char *start, const char *end);

/* ft_memcpy.c */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/* ft_atoi.c */
bool	ft_atoi(const char *n, int *res);

/* ft_atof.c */
bool	ft_atof(const char *n, __uint8_t precision, double *res);

/* ft_bzero.c */
void	ft_bzero(void *s, size_t n);

/* is_wspace.c */
bool	is_wspace(char c);

#endif /*STR_H*/
