/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:50 by me                #+#    #+#             */
/*   Updated: 2026/11/18 18:49:03 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

t_err	render(t_graphics *data, t_scene *sc)
{
	data->axes = get_system(sc->cam.vec);
	data->ox = tan(deg_to_rad(sc->cam.fov) / 2);
	data->oy = data->ox * (double)HEIGHT / (double)WIDTH;
	render_lines(0, HEIGHT, data, sc);
	return (ok);
}
