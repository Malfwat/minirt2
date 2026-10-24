/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:31:00 by me                #+#    #+#             */
/*   Updated: 2026/10/24 16:07:49 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

char	*ft_strdup(const char *str)
{
	char	*s;
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	if (!len)
		return (NULL);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = 0;
	i = 0;
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	return (s);
}

// char	*ft_strdup_range(const char *start, const char *end)
// {
// 	size_t	len;
// 	char	*ptr;

// 	if (end < start)
// 		return (NULL);
// 	len = (size_t)(end - start + 1);
// 	ptr = malloc(sizeof(char) * (len + 1));
// 	if (!ptr)
// 		return (NULL);
// 	ptr[len--] = 0;
// 	while (start <= end)
// 		ptr[len--] = *(end--);
// 	return (ptr);
// }
