/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_vec_ops_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 02:53:01 by me                #+#    #+#             */
/*   Updated: 2026/11/27 03:31:50 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_render.h"

#include <math.h>

//static void	get_uv_sp(t_hit hit, t_obj *obj, double *u, double *v)
//{
//	double	pol;
//	double	azim;
//	t_vec3	d;

//	d = sub(hit.p, obj->coordinate);
//	pol = acos(d.y / (obj->diameter / 2));
//	azim = atan2(d.z, d.x);
//	*u = (azim + M_PI) / (2 * M_PI);
//	*v = pol / M_PI;
//}

#include <stdio.h>

t_vec3	texture_vec(t_obj *obj, t_texel *pos)
{
	t_color	c;
	t_vec3	vec;

	if (pos->x == obj->normals->width - 1 || pos->y == obj->normals->height - 1)
		c = ppm_to_tcolor(obj->normals, pos->x, pos->y);
	else
		c = texel_interpolate(obj->normals, pos->x, pos->y);
	vec.x = (c.r / 255.0) * 2 - 1;
	vec.y = (c.g / 255.0) * 2 - 1;
	vec.z = (c.b / 255.0) * 2 - 1;
	vec = normalize(vec);
	printf("%f, %f, %f\n", vec.x, vec.y, vec.z);
	return (vec);
}
