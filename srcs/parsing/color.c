/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 20:14:07 by me                #+#    #+#             */
/*   Updated: 2026/11/11 20:59:38 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_parsing.h"
#include "rt_error.h"
#include "str.h"

__UINT8_TYPE__	*get_right_color_addr(t_color **color, int i)
{
	if (i == 0)
		return (&(*color)->r);
	if (i == 1)
		return (&(*color)->g);
	return (&(*color)->b);
}

char	*pass_color_value(char *str, int i)
{
	char	*ptr;

	ptr = ft_strchr(str, ',');
	if (i < 2 && !ptr)
		return ((void *)0);
	else if (i == 2)
	{
		if (ptr)
			return ((void *)0);
		ptr = ft_strchr_set(str, " \t\v\n\r\f");
		if (is_numeric(str))
			return (ft_strchr(str, 0));
		else
			return ((void *)0);
	}
	return (ptr);
}

t_err	get_color(char *str, t_color *color)
{
	int		value;
	int		i;
	char	*ptr;

	i = 0;
	while (i < 3)
	{
		ptr = pass_color_value(str, i);
		if (!ptr)
			return (bad_color_format);
		if (!ft_atoi(str, &value) || !(value >= 0 && value <= 255))
			return (invalid_color_value);
		*get_right_color_addr(&color, i) = value;
		if (i < 2)
		{
			str = ptr + 1;
			str += (*str == ' ');
		}
		i++;
	}
	if (str && !is_line_empty(str))
		return (bad_color_format);
	return (ok);
}
