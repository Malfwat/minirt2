/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_loop_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:14:30 by me                #+#    #+#             */
/*   Updated: 2026/11/21 20:50:44 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_graphics_bonus.h"
#include "mlx.h"

#include <sys/time.h>
#include <errno.h>
#include <stdio.h>

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

void	*monitor(void *data)
{
	t_render	*param;
	t_time		before;
	t_time		after;
	long		delta;

	param = data;
	printf("Went\n");
	gettimeofday(&before, NULL);
	for (int i = 0; i < 8; i++)
		sem_wait(&param->done);
	gettimeofday(&after, NULL);
	delta = (after.tv_sec - before.tv_sec) * 1000000 + after.tv_usec - before.tv_usec;
	printf("%i\t%lu\n", FREQ, delta);
	return (0);
}

void	launch_monitor(t_render *param)
{
	t_err	err;

	err = pthread_create(&param->monitor, NULL, monitor, param);
	if (err)
	{
		errno = err;
		return ;
	}
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
	if (delayed(now, param->last, FREQ)) // needs to be a define
		refresh(param, now);
	if (!stop)
	{
		launch_monitor(param);
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
