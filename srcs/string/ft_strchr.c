/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:21:21 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:25:11 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, char c)
{
	if (!s)
		return ((void *)0);
	while (*s && *s != c)
		s++;
	if (c == *s)
		return ((char *)s);
	return ((void *)0);
}

char	*ft_strchr_set(const char *s, char *set)
{
	if (!s)
		return ((void *)0);
	while (*s && !ft_strchr(set, *s))
		s++;
	if (*s && ft_strchr(set, *s))
		return ((char *)s);
	return ((void *)0);
}
