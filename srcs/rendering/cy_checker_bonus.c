/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_checker_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 18:20:39 by me                #+#    #+#             */
/*   Updated: 2026/11/25 00:58:13 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_config.h"
#include "rt_render.h"
#include "rt_struct.h"
#include <math.h>

t_color	disk_checker(t_hit hit, t_obj *obj)
{
	return (pl_checker(hit, obj));
}

static void	get_uv_cy(t_hit hit, t_obj *obj, double *u, double *v)
{
	double	tour;
	t_vec3	d;
	t_axes	h_axes;
	double	n;

	d = sub(hit.p, obj->coordinate);
	h_axes = get_system(obj->vec);
	tour = M_PI * obj->diameter;
	n = 2 * round(tour / (2 * obj->checker_size));
	if (n < 2)
		n = 2;
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
	get_uv_cy(hit, obj, &u, &v);
	c = obj->color;
	if ((int)(floor(u) + floor(v)) % 2 != 0)
		return ((t_color){c.r * DARKEN, c.g * DARKEN, c.b * DARKEN});
	return (c);
}

static void	get_uv_co(t_hit hit, t_obj *obj, double *u, double *v)
{
	t_axes	axes;
	t_vec3	d;
	double	azim;
	double	n;
	double	tour;

	tour = M_PI * obj->diameter;
	d = sub(hit.p, obj->coordinate);
	n = 2 * round(tour / (2 * obj->checker_size));
	axes = get_system(obj->vec);
	azim = atan2(scal(d, axes.y), scal(d, axes.x));
	*u = (azim + M_PI) / (2 * M_PI) * n;
	*v = get_norme(d) / (tour / n);
}

t_color	co_checker(t_hit hit, t_obj *obj)
{
	double	u;
	double	v;
	t_color	c;

	if (1 - fabs(scal(hit.normal, obj->vec)) < 1e-2)
	{
		hit.normal = obj->vec;
		return (disk_checker(hit, obj));
	}
	get_uv_co(hit, obj, &u, &v);
	c = obj->color;
	if ((int)(floor(u) + floor(v)) % 2 != 0)
		return ((t_color){c.r * DARKEN, c.g * DARKEN, c.b * DARKEN});
	return (c);
}
