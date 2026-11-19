/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:52:40 by me                #+#    #+#             */
/*   Updated: 2026/11/19 23:32:33 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_math.h"
#include "str.h"

#include <math.h>

t_axes	get_system(t_vec3 z)
{
	t_axes	axe;
	t_vec3	tmp;

	z = normalize(z);
	axe.z = z;
	ft_bzero(&tmp, sizeof(tmp));
	if (fabs(z.y) > 0.9999)
		tmp.x = 1;
	else
		tmp.y = 1;
	axe.x = cross(tmp, axe.z);
	axe.y = cross(axe.z, axe.x);
	return (axe);
}

void	build_frame(t_graphics *data, t_scene *sc)
{
	data->axes = get_system(sc->cam.vec);
	data->ox = tan(deg_to_rad(sc->cam.fov) / 2);
	data->oy = data->ox * (double)HEIGHT / (double)WIDTH;
}

t_vec3	pxl_to_sysvec(double ox, double oy, double posx, double posy)
{
	t_vec3	vec;

	vec.x = (posx * 2 / WIDTH - 1) * ox;
	vec.y = (1 - posy * 2 / HEIGHT) * oy;
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
