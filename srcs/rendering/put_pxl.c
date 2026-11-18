/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:47:55 by me                #+#    #+#             */
/*   Updated: 2026/11/18 17:13:13 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

#include <math.h>

void	put_pxl(int x, int y, t_graphics *data, int color)
{
	char	*dst;

	dst = data->image.addr
		+ (y * data->image.line_length
			+ x * (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}

t_color	get_pxl_color(t_scene *sc, int x, int y, double ox, double oy)
{
	double	tmp;
	t_color	c;

	(void)sc;
	tmp = (double)x * ox;
	c.r = tmp * 256;
	tmp = (double)y * oy;;
	c.g = tmp * 256;
	c.b = 1;
	return (c);
}

void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc)
{
	double	r;
	double	ox;
	double	oy;
	int		x;
	t_color	c;

	r = HEIGHT / WIDTH;
	ox = tan(sc->cam.fov / 2);
	oy = tan(sc->cam.fov / 2 * r);
	while (y_start < y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = get_pxl_color(sc, x, y_start, ox, oy);
			put_pxl(x, y_start, data, t_color_to_int(c));
			x++;
		}
		y_start++;
	}
}
