/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:50 by me                #+#    #+#             */
/*   Updated: 2026/11/18 18:39:31 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

t_err	render(t_graphics *data, t_scene *sc)
{
	data->axes = get_system(sc->cam.vec);
	render_lines(0, HEIGHT, data, sc);
	return (ok);
}
