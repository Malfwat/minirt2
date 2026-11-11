/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 20:14:07 by me                #+#    #+#             */
/*   Updated: 2026/11/11 20:33:40 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "str.h"

__UINT8_TYPE__	*get_right_color_addr(t_color **color, int i)
{
	if (i == 0)
		return (&(*color)->r);
	if (i == 0)
		return (&(*color)->g);
	return (&(*color)->b);
}

t_err	get_color(char *str, t_color *color)
{
	int		value;
	int		i;
	char	*ptr;

	i = 0;
	while (i < 3)
	{
		ptr = ft_strchr(str, ',');
		if (!ptr && i < 2)
			return (bad_color_format);
		if (ptr)
			*ptr = 0;
		if (!ft_atoi(str, &value) || !(value >= 0 && value <= 255))
			return (invalid_color_value);
		*get_right_color_addr(&color, i) = value;
		if (*ptr && i < 2)
			str = ptr + 1;
		str += (*str == ' ');
		i++;
	}
	return (ok);
}
