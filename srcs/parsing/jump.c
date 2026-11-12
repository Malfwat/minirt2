/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:49:11 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:00:34 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	jump_id(char **str_ptr)
{
	char	*ptr;

	ptr = *str_ptr;
	ptr = ft_strchr_set(ptr, " \t\v\r\f");
	if (!ptr)
		ptr = ft_strchr(ptr, 0);
	while (*ptr && ft_strchr("\t\v\r\f ", *ptr))
		ptr++;
	*str_ptr = ptr;
}
