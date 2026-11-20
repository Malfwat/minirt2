/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_quad.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 00:13:19 by me                #+#    #+#             */
/*   Updated: 2026/11/20 00:32:18 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "str.h"
#include "rt_math.h"

t_color_double	add_color_double(t_color_double c, t_color x)
{
	c.r += (double)x.r;
	c.g += (double)x.g;
	c.b += (double)x.b;
	return (c);
}

t_color	cdouble_to_c(t_color_double c, double div)
{
	return ((t_color){c.r / div, c.g / div, c.b / div});
}

t_quadrant	get_quadrant(t_graphics *data, t_scene *sc, double x, double y)
{
	t_quadrant	q;

	q.colors[0] = get_pxl_color(sc, data, x + 0.25, y + 0.25);
	q.colors[1] = get_pxl_color(sc, data, x + 0.25, y + 0.75);
	q.colors[2] = get_pxl_color(sc, data, x + 0.75, y + 0.25);
	q.colors[3] = get_pxl_color(sc, data, x + 0.75, y + 0.75);
	return (q);
}

t_color	quadrant_mean(t_quadrant q)
{
	t_color_double	tmp;
	int				i;

	ft_bzero(&tmp, sizeof(tmp));
	i = 0;
	while (i < 4)
		tmp = add_color_double(tmp, q.colors[i++]);
	return (cdouble_to_c(tmp, 4));
}
