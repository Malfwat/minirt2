/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:50 by me                #+#    #+#             */
/*   Updated: 2026/11/22 19:39:39 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

#include "mlx.h"

t_err	render(t_graphics *data, t_scene *sc, int i, int b[])
{
	int	y;

	y = ligne(i, b[0], b[1], b[2]);
	render_lines(y, y + 1, data, sc);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (ok);
}
