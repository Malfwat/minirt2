/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:27:18 by me                #+#    #+#             */
/*   Updated: 2026/11/24 18:24:59 by me               ###   ########.fr       */
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

static void	get_uv_sp(t_hit hit, t_obj *obj, double *u, double *v)
{
	double	pol;
	double	azim;
	double	n;
	t_vec3	d;
	double	tour;

	tour = M_PI * obj->diameter;
	d = sub(hit.p, obj->coordinate);
	n = 2 * round(tour / (2 * obj->checker_size));
	pol = acos(d.y / (obj->diameter / 2));
	azim = atan2(d.z, d.x);
	*u = (azim + M_PI) / (2 * M_PI) * n;
	*v = pol * (obj->diameter / 2) / (tour / n);
}

t_color	sp_checker(t_hit hit, t_obj *obj)
{
	t_color	c;
	double	u;
	double	v;

	get_uv_sp(hit, obj, &u, &v);
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
	else if (obj->id == sphere)
		return (sp_checker(hit, obj));
	return (obj->color);
}
