/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:47:55 by me                #+#    #+#             */
/*   Updated: 2026/11/19 02:11:20 by me               ###   ########.fr       */
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

t_vec3	pxl_to_sysvec(double ox, double oy, double posx, double posy)
{
	t_vec3	vec;

	vec.x = ((posx + 0.5) * 2 / WIDTH - 1) * ox;
	vec.y = (1 - (posy + 0.5) * 2 / HEIGHT) * oy;
	vec.z = 1;
	return (vec);
}

t_vec3	sysvec_to_real_vec(t_axes axes, t_vec3 svec)
{
	t_vec3	vec;

	vec.x = svec.x * axes.x.x + svec.y * axes.y.x + svec.z * axes.z.x;
	vec.y = svec.x * axes.x.y + svec.y * axes.y.y + svec.z * axes.z.y;
	vec.z = svec.x * axes.x.z + svec.y * axes.y.z + svec.z * axes.z.z;
	return (normalize(vec));
}

t_color	get_pxl_color(t_scene *sc, t_graphics *d, double x, double y)
{
	t_obj	*lst;
	t_vec3	vec;
	t_hit	best;
	t_hit	hit;

	ft_bzero(&hit, sizeof(hit));
	ft_bzero(&best, sizeof(best));
	best.t = INFINITY;
	vec = sysvec_to_real_vec(d->axes, pxl_to_sysvec(d->ox, d->oy, x, y));
	lst = sc->obj_lst;
	while (lst)
	{
		if (get_intersect_f(lst->id)(lst, vec, sc->cam.coordinate, &hit))
		{
			if (hit.t < best.t && hit.t > 0)
				best = hit;
		}
		lst = lst->next;
	}
	if (!best.obj)
		return ((t_color){0, 0, 0});
	return (get_final_color(best, sc->light_lst, sc->amb));
}

void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc)
{
	int		x;
	t_color	c;

	while (y_start < y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = get_pxl_color(sc, data, x, y_start);
			put_pxl(x, y_start, data, t_color_to_int(c));
			x++;
		}
		y_start++;
	}
}
