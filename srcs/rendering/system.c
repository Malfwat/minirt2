/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:52:40 by me                #+#    #+#             */
/*   Updated: 2026/11/18 19:14:17 by me               ###   ########.fr       */
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
	{
		tmp.x = 1;
		axe.y = cross(axe.z, tmp);
		axe.x = cross(axe.y, axe.z);
	}
	else
	{
		tmp.y = 1;
		axe.x = cross(axe.z, tmp);
		axe.y = cross(axe.x, axe.z);
	}
	return (axe);
}

void	build_frame(t_graphics *data, t_scene *sc)
{
	data->axes = get_system(sc->cam.vec);
	data->ox = tan(deg_to_rad(sc->cam.fov) / 2);
	data->oy = data->ox * (double)HEIGHT / (double)WIDTH;
}
