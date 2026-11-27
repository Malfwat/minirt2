/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xy_ppm_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 17:24:00 by me                #+#    #+#             */
/*   Updated: 2026/11/27 17:28:04 by me               ###   ########.fr       */
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
}

void	get_xy_pl(t_hit hit, t_obj *obj, t_texel *indexes)
{
	t_axes	hit_axes;

	hit_axes = get_system(hit.normal);
	indexes->x = scal(sub(hit.p, obj->coordinate), hit_axes.x) / TEXTURE_SIZE;
	indexes->y = scal(sub(hit.p, obj->coordinate), hit_axes.y) / TEXTURE_SIZE;
	indexes->x = fabs(indexes->x);
	indexes->x -= floor(indexes->x);
	indexes->y = fabs(indexes->y);
	indexes->y -= floor(indexes->y);
}
