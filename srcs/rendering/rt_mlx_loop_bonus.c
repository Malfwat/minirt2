/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_loop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:14:30 by me                #+#    #+#             */
/*   Updated: 2026/11/22 00:50:27 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_graphics_bonus.h"
#include "mlx.h"

int	keyhook(int keycode, void *param)
{
	t_render	*render_param;

	render_param = param;
	if (keycode == ESC)
	{
		stop_and_join_thread(render_param->sem_stop,
			render_param->stop,
			render_param->tab,
			NB_TH);
		mlx_loop_end(render_param->data.mlx);
	}
	return (0);
}

bool	delayed(t_time n, t_time l, long t)
{
	long	delay;

	delay = n.tv_sec * 1000000 + n.tv_usec;
	delay = delay - l.tv_sec * 1000000 - l.tv_usec;
	return (delay > t);
}

void	refresh(t_render *param, t_time now)
{
	param->last = now;
	sem_n_wait(param->sem_printing, NB_TH);
	mlx_put_image_to_window(param->data.mlx, param->data.win,
		param->data.image.img, 0, 0);
	sem_n_post(param->sem_printing, NB_TH);
}

int	rendering_loop(void *data)
{
	static bool	stop;
	t_render	*param;
	t_time		now;
	int			err;

	param = data;
	err = gettimeofday(&now, NULL);
	if (err)
	{
		param->err = syscall_err;
		return (mlx_loop_end(param->data.mlx), 0);
	}
	if (delayed(now, param->last, PERIOD)) // needs to be a define
		refresh(param, now);
	if (!stop)
	{
		param->err = render_th(param);
		if (param->err != ok)
			return (mlx_loop_end(param->data.mlx), 0);
		stop = true;
	}
	return (0);
}

int	stop_loop(void *data)
{
	t_render	*param;

	param = data;
	stop_and_join_thread(param->sem_stop, param->stop, param->tab, NB_TH);
	mlx_loop_end(param->data.mlx);
	return (0);
}
