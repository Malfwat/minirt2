/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 03:26:37 by me                #+#    #+#             */
/*   Updated: 2026/11/22 16:40:20 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"
#include "rt_graphics.h"
#include "rt_graphics_bonus.h"

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

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

void	compute_line(t_thread_data *data, int cursor)
{
	data->index = ligne(cursor, data->b2, data->b3, data->b4);
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
