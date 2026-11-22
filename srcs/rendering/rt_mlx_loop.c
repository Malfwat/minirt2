/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:14:30 by me                #+#    #+#             */
/*   Updated: 2026/11/22 19:44:38 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt.h"
#include "mlx.h"

#include <stdbool.h>

int	keyhook(int keycode, void *param)
{
	t_rt	*rt;

	rt = param;
	if (keycode == ESC)
		rt->stop = true;
	return (0);
}

int	rendering_loop(void *param)
{
	static int	i;
	static int	b[3];
	t_rt		*rt;

	rt = param;
	if (rt->stop)
		return (mlx_loop_end(rt->data.mlx), 0);
	if (i == 0)
	{
		fill_bases(b);
		build_frame(&rt->data, &rt->sc);
	}
	if (i < HEIGHT)
	{
		render(&rt->data, &rt->sc, i, b);
		i++;
	}
	return (0);
}

int	stop_loop(void *param)
{
	mlx_loop_end(((t_graphics *)param)->mlx);
	return (0);
}
