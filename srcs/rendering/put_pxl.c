/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:47:55 by me                #+#    #+#             */
/*   Updated: 2026/11/18 18:29:22 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_math.h"

#include <math.h>

void	put_pxl(int x, int y, t_graphics *data, int color)
{
	char	*dst;

	dst = data->image.addr
		+ (y * data->image.line_length
			+ x * (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}

t_color	get_pxl_color(t_scene *sc, double xy[], double ox, double oy)
{
	t_vec3	vec;
	t_color	c;

	(void)sc;
	vec.x = ((xy[0] + 0.5) * 2 / WIDTH - 1) * ox;
	vec.y = (1 - (xy[1] + 0.5) * 2 / HEIGHT) * oy;
	vec.z = 1;
	vec = normalize(vec);
	c.r = (vec.x + 1) / 2 * 255;
	c.g = (vec.y + 1) / 2 * 255;
	c.b = vec.z * 255;
	return (c);
}

void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc)
{
	double	r;
	double	ox;
	double	oy;
	int		x;
	t_color	c;

	r = (double)HEIGHT / (double)WIDTH;
	ox = tan(deg_to_rad(sc->cam.fov) / 2);
	oy = tan(deg_to_rad(sc->cam.fov) / 2) * r;
	while (y_start < y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = get_pxl_color(sc, (double []){x, y_start}, ox, oy);
			put_pxl(x, y_start, data, t_color_to_int(c));
			x++;
		}
		y_start++;
	}
}
