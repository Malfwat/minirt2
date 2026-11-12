/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:36:50 by me                #+#    #+#             */
/*   Updated: 2026/11/12 17:37:33 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

bool	is_line_empty(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (false);
		str++;
	}
	return (true);
}

void	null_terminate_component(char *str)
{
	char	*ptr;

	ptr = ft_strchr_set(str, "\t\v\n\r\f ");
	if (!ptr)
		ptr = ft_strchr(str, 0);
	*ptr = 0;
}
