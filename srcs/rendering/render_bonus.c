/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/16 15:27:06 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct s_thread_data
{
	t_graphics	*data;
	t_scene		*sc;
	bool		*go_on;
	int			y_start;
	int			y_end;
	sem_t		*sem;
}	t_thread_data;

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

void	render(t_graphics *data, t_scene *sc)
{
	__UINT8_TYPE__	i;
	int				y;
	bool			go_on;
	sem_t			sem;
	pthread_t		tab[NB_TH];
	t_thread_data	thread_data[NB_TH];

	i = 0;
	y = 0;
	go_on = true;
	if (sem_init(&sem, 0, 1))
		return ;
	while (i < NB_TH)
	{
		thread_data[i].data = data;
		thread_data[i].sc = sc;
		thread_data[i].sem = &sem;
		thread_data[i].go_on = &go_on;
		thread_data[i].y_start = y;
		y += HEIGHT / NB_TH;
		y += (int []){0, 1}[i < HEIGHT % NB_TH];
		thread_data[i].y_end = y;
		if (pthread_create(tab + i, NULL, thread_rendering, thread_data + i))
			break ;
		i++;
	}
	if (i < NB_TH)
	{
		sem_wait(&sem);
		go_on = false;
		sem_post(&sem);
		while (i > 0)
			pthread_join(tab[--i], NULL);
		return ;
	}
	i = 0;
	while (i < NB_TH)
		pthread_join(tab[i++], NULL);
}
