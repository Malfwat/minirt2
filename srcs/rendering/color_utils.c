/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 01:59:33 by me                #+#    #+#             */
/*   Updated: 2026/11/27 02:07:05 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_color.h"

unsigned int	double_to_ui_color(double val)
{
	double	rounded_val;

	rounded_val = round(val);
	if (rounded_val < 0)
		rounded_val = 0;
	if (rounded_val > 255)
		rounded_val = 255;
	return (rounded_val);
}

t_color	cdouble_to_c(t_color_double c, double div)
{
	t_color	color;

	color.r = double_to_ui_color(c.r / div);
	color.g = double_to_ui_color(c.g / div);
	color.b = double_to_ui_color(c.b / div);
	return (color);
}
