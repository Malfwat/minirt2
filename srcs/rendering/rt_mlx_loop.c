/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:14:30 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:18:24 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_config.h"
#include "rt_display.h"
#include "rt_render.h"
#include "rt.h"
#include "mlx.h"

#include <stdbool.h>
#include <sys/time.h>

int	keyhook(int keycode, void *param)
{
	t_rt	*rt;

	rt = param;
	if (keycode == ESC)
		rt->stop = true;
	return (0);
}

static void	initialize_loop(t_rt *rt, int b[])
{
	gettimeofday(&rt->last, 0);
	fill_bases(b);
	build_frame(&rt->data, &rt->sc);
}

t_err	render(t_graphics *data, t_scene *sc, int i, int b[])
{
	int	y;

	y = ligne(i, b[0], b[1], b[2]);
	render_lines(y, y + 1, data, sc);
	return (ok);
}

int	rendering_loop(void *param)
{
	int			ret;
	static int	i;
	static int	b[3];
	t_rt		*rt;
	t_time		now;

	rt = param;
	if (rt->stop)
		return (mlx_loop_end(rt->data.mlx), 0);
	if (i == 0)
		initialize_loop(rt, b);
	if (i < HEIGHT)
	{
		render(&rt->data, &rt->sc, i, b);
		ret = gettimeofday(&now, 0);
		if (ret || delayed(now, rt->last, PERIOD))
		{
			mlx_put_image_to_window(rt->data.mlx, rt->data.win,
				rt->data.image.img, 0, 0);
			if (!ret)
				rt->last = now;
		}
		i++;
	}
	return (0);
}

int	stop_loop(void *param)
{
	mlx_loop_end(((t_graphics *)param)->mlx);
	return (0);
}
