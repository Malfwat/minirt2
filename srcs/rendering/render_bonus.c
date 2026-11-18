/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/18 18:26:46 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"
#include "rt_graphics.h"
#include "rt_thread_bonus.h"

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
		render_lines(data->y_start, data->y_start + 1, data->data, data->sc);
		data->y_start++;
		sem_wait(data->sem);
		if (*data->stop)
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

void	stop_and_join_thread(sem_t *sem, bool *stop, pthread_t tab[], int n)
{
	sem_wait(sem);
	*stop = true;
	sem_post(sem);
	join_thread(tab, n);
}

t_thread_data	attrib_data(t_graphics *data, t_scene *sc, sem_t *sem, bool *s)
{
	t_thread_data	tmp;

	tmp.data = data;
	tmp.sc = sc;
	tmp.sem = sem;
	tmp.stop = s;
	return (tmp);
}

t_err	render(t_graphics *data, t_scene *sc)
{
	struct s_multi_threading	th;
	pthread_t					tab[NB_TH];
	t_thread_data				th_data[NB_TH];
	int							i;

	ft_bzero(&th, sizeof(th));
	if (sem_init(&th.sem, 0, 1))
		return (syscall_err);
	data->axes = get_system(sc->cam.vec);
	i = -1;
	while (++i < NB_TH)
	{
		th_data[i] = attrib_data(data, sc, &th.sem, &th.stop);
		th_data[i].y_start = th.lim;
		th.lim += HEIGHT / NB_TH + (int []){0, 1}[i < HEIGHT % NB_TH];
		th_data[i].y_end = th.lim;
		th.err = pthread_create(tab + i, NULL, thread_rendering, th_data + i);
		if (th.err)
		{
			errno = th.err;
			stop_and_join_thread(&th.sem, &th.stop, tab, i);
			return (syscall_err);
		}
	}
	return (join_thread(tab, NB_TH), ok);
}
