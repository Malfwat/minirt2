/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/16 20:44:06 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_graphics.h"
#include "rt_thread_bonus.h"

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void	*thread_rendering(void *tdata)
{
	t_thread_data	*data;

	data = tdata;
	while (data->y_start < data->y_end)
	{
		render_lines(data->y_start, data->y_start + 1, data->data, data->sc);
		data->y_start++;
		sem_wait(data->sem);
		if (!*data->go_on)
		{
			sem_post(data->sem);
			break ;
		}
		sem_post(data->sem);
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

void	stop_and_join_thread(sem_t *sem, bool *go_on, pthread_t tab[], int n)
{
	sem_wait(sem);
	*go_on = false;
	sem_post(sem);
	join_thread(tab, n);
}

t_thread_data	attrib_data(t_graphics *data, t_scene *sc, sem_t *sem, bool *go)
{
	t_thread_data	tmp;

	tmp.data = data;
	tmp.sc = sc;
	tmp.sem = sem;
	tmp.go_on = go;
	return (tmp);
}

t_err	render(t_graphics *data, t_scene *sc)
{
	struct s_multi_threading	th;
	pthread_t					tab[NB_TH];
	t_thread_data				thread_data[NB_TH];
	__UINT8_TYPE__				i;

	if (sem_init(&th.sem, 0, 1))
		return (syscall_err);
	i = 0;
	th.band_limit = 0;
	th.go_on = true;
	while (i < NB_TH)
	{
		thread_data[i] = attrib_data(data, sc, &th.sem, &th.go_on);
		thread_data[i].y_start = th.band_limit;
		th.band_limit += HEIGHT / NB_TH;
		th.band_limit += (int []){0, 1}[i < HEIGHT % NB_TH];
		thread_data[i].y_end = th.band_limit;
		if (pthread_create(tab + i, NULL, thread_rendering, thread_data + i))
			return (stop_and_join_thread(&th.sem, &th.go_on, tab, i - 1),
				syscall_err);
		i++;
	}
	return (join_thread(tab, NB_TH), ok);
}
