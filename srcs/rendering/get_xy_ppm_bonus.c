/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xy_ppm_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 17:24:00 by me                #+#    #+#             */
/*   Updated: 2026/11/28 04:24:58 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_config.h"
#include "rt_struct.h"
#include "rt_render.h"

#include <math.h>

void	get_xy_sp(t_hit hit, t_obj *obj, t_texel *indexes)
{
	double	pol;
	double	azim;
	t_vec3	d;

	d = sub(hit.p, obj->coordinate);
	pol = acos(d.y / (obj->diameter / 2));
	azim = atan2(d.z, d.x);
	indexes->x = (azim + M_PI) / (2 * M_PI);
	indexes->y = pol / M_PI;
	indexes->axes = get_system(hit.normal);
	indexes->axes.x = mult(indexes->axes.x, -1);
	indexes->axes.y = mult(indexes->axes.y, -1);
}

void	get_xy_pl(t_hit hit, t_obj *obj, t_texel *pos)
{
	pos->axes = get_system(hit.normal);
	pos->x = scal(sub(hit.p, obj->coordinate), pos->axes.x) / TEXTURE_SIZE;
	pos->y = scal(sub(hit.p, obj->coordinate), pos->axes.y) / TEXTURE_SIZE;
	pos->x = fabs(pos->x);
	pos->x -= floor(pos->x);
	pos->y = fabs(pos->y);
	pos->y -= floor(pos->y);
}

void	get_xy_cy(t_hit hit, t_obj *obj, t_texel *pos)
{
	t_axes	tmp;
	t_vec3	d;
	double	cir;
	double	u;
	double	v;

	if (1 - fabs(scal(hit.normal, obj->vec)) < 1e-3)
		return (get_xy_pl(hit, obj, pos));
	d = sub(hit.p, obj->coordinate);
	d = sub(d, mult(obj->vec, obj->height / 2));
	tmp = get_system(obj->vec);
	cir = M_PI * obj->diameter;
	pos->x = scal(d, tmp.x);
	pos->y = scal(d, tmp.y);
	u = (atan2(pos->y, pos->x) + M_PI) / (2 * M_PI);
	v = scal(d, obj->vec) / cir;
	v = v - floor(v);
	pos->x = u;
	pos->y = v;
	tmp.x = cross(obj->vec, hit.normal);
	tmp.y = obj->vec;
	pos->axes = tmp;
}

void	get_xy_co(t_hit hit, t_obj *obj, t_texel *pos)
{
	t_axes	tmp;
	t_vec3	d;
	double	u;
	double	v;

	if (1 - fabs(scal(hit.normal, obj->vec)) < 1e-3)
		return (get_xy_pl(hit, obj, pos));
	d = sub(hit.p, obj->coordinate);
	tmp = get_system(obj->vec);
	pos->x = scal(d, tmp.x);
	pos->y = scal(d, tmp.y);
	u = (atan2(pos->y, pos->x) + M_PI) / (2 * M_PI);
	v = get_norme(d);
	v = v - floor(v);
	pos->x = u;
	pos->y = v;
	tmp.x = cross(obj->vec, hit.normal);
	tmp.y = obj->vec;
	pos->axes = tmp;
}