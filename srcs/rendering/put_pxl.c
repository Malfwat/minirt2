/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:47:55 by me                #+#    #+#             */
/*   Updated: 2026/11/22 23:08:53 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_config.h"
#include "rt_display.h"
#include "rt_render.h"
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
			if (quadrant_diff(q) > 20)
				c = anti_aliasing(data, sc, x, y_start);
			else
				c = quadrant_mean(q);
			put_pxl(x, y_start, data, t_color_to_int(c));
			x++;
		}
		y_start++;
	}
}
