/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:27:06 by me                #+#    #+#             */
/*   Updated: 2026/10/23 20:57:45 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stddef.h>

/* ft_strchr.c */
char	*ft_strchr(const char *s, char c);

/* ft_strcmp.c */
int		ft_strcmp(const char *s1, const char *s2);

/* ft_strlen.c */
size_t	ft_strlen(const char *str);

/* ft_strdup.c */
char	*ft_strdup(const char *str);
char	*ft_strdup_range(const char *start, const char *end);

#endif /*STR_H*/
