/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:47:55 by me                #+#    #+#             */
/*   Updated: 2026/11/20 00:08:53 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_math.h"
#include "rt_element.h"
#include "str.h"

void	put_pxl(int x, int y, t_graphics *data, int color)
{
	char	*dst;

	dst = data->image.addr
		+ (y * data->image.line_length
			+ x * (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}

bool	cast_ray(t_scene *sc, t_cast data, t_hit *ptr)
{
	t_obj	*olst;
	t_hit	best;
	t_hit	hit;

	ft_bzero(&best, sizeof(best));
	best.t = INFINITY;
	olst = sc->obj_lst;
	while (olst)
	{
		if (get_intersect_f(olst->id)(olst, data.dir, data.origin, &hit))
		{
			if (hit.t < best.t && hit.t > 0)
				best = hit;
		}
		olst = olst->next;
	}
	if (best.obj && best.t > 1e-4 && best.t < data.lim)
	{
		*ptr = best;
		return (true);
	}
	return (false);
}

t_color	get_pxl_color(t_scene *sc, t_graphics *d, double x, double y)
{
	t_cast	data;
	t_vec3	vec;
	t_hit	best;
	t_hit	hit;

	ft_bzero(&hit, sizeof(hit));
	vec = sysvec_to_real_vec(d->axes, pxl_to_sysvec(d->ox, d->oy, x, y));
	data.dir = vec;
	data.lim = INFINITY;
	data.origin = sc->cam.coordinate;
	if (!cast_ray(sc, data, &best))
		return ((t_color){0, 0, 0});
	return (get_final_color(best, sc));
}

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

void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc)
{
	int			x;
	t_color		c;
	t_quadrant	q;

	while (y_start < y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			q = get_quadrant(data, sc, x, y_start);
			c = quadrant_mean(q);
			put_pxl(x, y_start, data, t_color_to_int(c));
			x++;
		}
		y_start++;
	}
}
