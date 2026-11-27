/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_vec_ops_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 02:53:01 by me                #+#    #+#             */
/*   Updated: 2026/11/27 03:52:04 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_render.h"

t_color_double	texel_interpolate(t_ppm *tex, double x, double y)
{
	double			fx;
	double			fy;
	t_color_double	c;
	t_color_double	tmp;

	fx = x - (int)x;
	fy = y - (int)y;
	c = ppm_to_tcolor_double(tex, (int)x, (int)y);
	c = mult_color_ratio(c, (1 - fx) * (1 - fy));
	tmp = ppm_to_tcolor_double(tex, (int)x + 1, (int)y);
	tmp = mult_color_ratio(tmp, fx * (1 - fy));
	c = add_color_doubles(c, tmp);
	tmp = ppm_to_tcolor_double(tex, (int)x, (int)y + 1);
	tmp = mult_color_ratio(tmp, (1 - fx) * fy);
	c = add_color_doubles(c, tmp);
	tmp = ppm_to_tcolor_double(tex, (int)x + 1, (int)y + 1);
	tmp = mult_color_ratio(tmp, fx * fy);
	c = add_color_doubles(c, tmp);
	return (c);
}

t_vec3	texture_vec(t_obj *obj, t_texel *pos)
{
	t_color_double	c;
	t_vec3			vec;

	if (pos->x == obj->normals->width - 1 || pos->y == obj->normals->height - 1)
		c = ppm_to_tcolor_double(obj->normals, pos->x, pos->y);
	else
		c = texel_interpolate(obj->normals, pos->x, pos->y);
	vec.x = (c.r / 255.0) * 2 - 1;
	vec.y = (c.g / 255.0) * 2 - 1;
	vec.z = (c.b / 255.0) * 2 - 1;
	vec = normalize(vec);
	return (vec);
}
