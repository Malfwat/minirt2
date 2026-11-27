/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 22:21:54 by me                #+#    #+#             */
/*   Updated: 2026/11/27 02:10:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_render.h"
#include "rt_struct.h"

int	t_color_to_int(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

t_color	mult_color_light(t_color a, t_light light, double factor)
{
	t_color	c;

	c.r = a.r * (light.color.r / 255.0) * light.ratio * factor;
	c.g = a.g * (light.color.g / 255.0) * light.ratio * factor;
	c.b = a.b * (light.color.b / 255.0) * light.ratio * factor;
	return (c);
}

t_color_double	mult_color_ratio(t_color_double a, double ratio)
{
	a.r *= ratio;
	a.g *= ratio;
	a.b *= ratio;
	return (a);
}

t_color_double	add_color_doubles(t_color_double c, t_color_double x)
{
	c.r += (double)x.r;
	c.g += (double)x.g;
	c.b += (double)x.b;
	return (c);
}

t_color	add_color(t_color a, t_color b)
{
	t_color	c;
	int		tmp;

	tmp = (int)a.r + (int)b.r;
	if (tmp > 255)
		tmp = 255;
	c.r = tmp;
	tmp = (int)a.g + (int)b.g;
	if (tmp > 255)
		tmp = 255;
	c.g = tmp;
	tmp = (int)a.b + (int)b.b;
	if (tmp > 255)
		tmp = 255;
	c.b = tmp;
	return (c);
}
