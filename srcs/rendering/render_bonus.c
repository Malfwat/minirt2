/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/21 04:01:11 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"
#include "rt_graphics.h"
#include "rt_graphics_bonus.h"

#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void	*thread_rendering(void *tdata)
{
	t_thread_data	*data;

	data = tdata;
	while (data->y_start < data->y_end)
	{
		sem_wait(data->sem_printing);
		render_lines(data->y_start, data->y_start + 1, data->data, data->sc);
		data->y_start++;
		sem_wait(data->sem_stop);
		if (*data->stop)
		{
			sem_post(data->sem_printing);
			sem_post(data->sem_stop);
			break ;
		}
		sem_post(data->sem_printing);
		sem_post(data->sem_stop);
		usleep(1);
	}
	return (NULL);
}

void	join_thread(pthread_t tab[], int tab_size)
{
	int	i;

	i = 0;
	while (i < tab_size)
		pthread_join(tab[i++], NULL);
}

void	stop_and_join_thread(sem_t tab[], bool stop[],
	pthread_t th_tab[], int n)
{
	int	i;

	i = 0;
	while (i < NB_TH)
	{
		sem_wait(tab + i);
		stop[i] = true;
		sem_post(tab + i);
		i++;
	}
	join_thread(th_tab, n);
}

t_thread_data	attrib_data(t_render *params, int i)
{
	t_thread_data	tmp;

	tmp.data = &params->data;
	tmp.sc = &params->sc;
	tmp.sem_stop = &params->sem_stop[i];
	tmp.sem_printing = &params->sem_printing[i];
	tmp.stop = &params->stop[i];
	return (tmp);
}

t_err	render_th(t_render *param)
{
	int				i;
	int				lim;
	t_err			err;

	i = -1;
	lim = 0;
	while (++i < NB_TH)
	{
		param->th_data[i] = attrib_data(param, i);
		param->th_data[i].id = i;
		param->th_data[i].y_start = lim;
		lim += HEIGHT / NB_TH + (int []){0, 1}[i < HEIGHT % NB_TH];
		param->th_data[i].y_end = lim;
		err = pthread_create(param->tab + i, NULL,
				thread_rendering, param->th_data + i);
		if (err)
		{
			errno = err;
			stop_and_join_thread(param->sem_stop, param->stop, param->tab, i);
			return (close_sem_tab(param->sem_stop, NB_TH), syscall_err);
		}
	}
	return (ok);
}
