/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 00:13:19 by me                #+#    #+#             */
/*   Updated: 2026/11/27 01:59:46 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_config.h"
#include "rt_render.h"
#include "str.h"

t_color_double	add_color_double(t_color_double c, t_color x)
{
	c.r += (double)x.r;
	c.g += (double)x.g;
	c.b += (double)x.b;
	return (c);
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

t_color	anti_aliasing(t_graphics *data, t_scene *sc, double x, double y)
{
	int				total;
	int				i;
	int				j;
	double			step;
	t_color_double	c;

	total = AA * AA;
	step = 1.0 / AA;
	ft_bzero(&c, sizeof(c));
	i = 0;
	while (i < AA)
	{
		j = 0;
		while (j < AA)
		{
			c = add_color_double(c, get_pxl_color(sc, data,
						x + step * (double)(j + 0.5),
						y + step * (double)(i + 0.5)));
			j++;
		}
		i++;
	}
	return (cdouble_to_c(c, total));
}
