/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:27:18 by me                #+#    #+#             */
/*   Updated: 2026/11/24 17:46:34 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_config.h"
#include "rt_render.h"
#include "rt_struct.h"
#include <math.h>

t_color	pl_checker(t_hit hit, t_obj *obj)
{
	double	u;
	double	v;
	t_color	c;
	t_axes	hit_axes;

	hit_axes = get_system(hit.normal);
	u = scal(sub(hit.p, obj->coordinate), hit_axes.x) / obj->checker_size;
	v = scal(sub(hit.p, obj->coordinate), hit_axes.y) / obj->checker_size;
	c = obj->color;
	if ((int)(floor(u) + floor(v)) % 2 != 0)
		return ((t_color){c.r * DARKEN, c.g * DARKEN, c.b * DARKEN});
	return (c);
}

t_color	disk_checker(t_hit hit, t_obj *obj)
{
	return (pl_checker(hit, obj));
}

static void	get_uv(t_hit hit, t_obj *obj, double *u, double *v)
{
	double	tour;
	t_vec3	d;
	t_axes	h_axes;
	double	n;

	d = sub(hit.p, obj->coordinate);
	h_axes = get_system(obj->vec);
	tour = M_PI * obj->diameter;
	n = round(tour / obj->checker_size);
	*u = (atan2(scal(d, h_axes.y), scal(d, h_axes.x)) + M_PI) / (2 * M_PI) * n;
	*v = scal(d, obj->vec) / (tour / n);
}

t_color	cy_checker(t_hit hit, t_obj *obj)
{
	double	u;
	double	v;
	t_color	c;

	if (1 - fabs(scal(hit.normal, obj->vec)) < 1e-2)
	{
		hit.normal = obj->vec;
		return (disk_checker(hit, obj));
	}
	get_uv(hit, obj, &u, &v);
	c = obj->color;
	if ((int)(floor(u) + floor(v)) % 2 != 0)
		return ((t_color){c.r * DARKEN, c.g * DARKEN, c.b * DARKEN});
	return (c);
}

t_color	checker_color(t_hit hit, t_obj *obj)
{
	if (obj->id == plan)
		return (pl_checker(hit, obj));
	else if (obj->id == cylinder)
		return (cy_checker(hit, obj));
	return (obj->color);
}
