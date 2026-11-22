/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/22 02:14:15 by me               ###   ########.fr       */
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

#include <stdio.h>

int	ligne(int cursor)
{
	if (cursor < HEIGHT / 8)
		return (8 * cursor);
	else if (cursor < HEIGHT / 4)
		return (8 * (cursor - HEIGHT / 8) + 4);
	else if (cursor < HEIGHT / 2)
		return (4 * (cursor - HEIGHT / 4) + 2);
	return (2 * (cursor - HEIGHT / 2) + 1);
}

void	compute_line(t_thread_data *data, int cursor)
{
	data->index = ligne(cursor);
	sem_wait(data->sem_printing);
	render_lines(data->index, data->index + 1, data->data, data->sc);
	sem_post(data->sem_printing);
}

void	*thread_rendering(void *tdata)
{
	t_thread_data	*data;
	int				cursor;

	data = tdata;
	sem_wait(data->sem_band);
	cursor = *data->cursor;
	while (cursor < HEIGHT)
	{
		*data->cursor += 1;
		sem_post(data->sem_band);
		compute_line(data, cursor);
		sem_wait(data->sem_stop);
		if (*data->stop)
		{
			sem_post(data->sem_stop);
			break ;
		}
		sem_post(data->sem_stop);
		usleep(1);
		sem_wait(data->sem_band);
		cursor = *data->cursor;
	}
	sem_post(data->sem_band);
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
	tmp.cursor = &params->band_cursor;
	tmp.sem_band = &params->sem_cursor;
	return (tmp);
}

t_err	render_th(t_render *param)
{
	int				i;
	t_err			err;

	i = -1;
	while (++i < NB_TH)
	{
		param->th_data[i] = attrib_data(param, i);
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
