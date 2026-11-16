/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/16 14:55:08 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

#include <unistd.h>
#include <pthread.h>

typedef struct s_thread_data
{
	t_graphics	*data;
	t_scene		*sc;
	int			y_start;
	int			y_end;
}	t_thread_data;

void	*thread_rendering(void *tdata)
{
	t_thread_data	*data;

	data = tdata;
	render_lines(data->y_start, data->y_end, data->data, data->sc);
	return (NULL);
}

void	render(t_graphics *data, t_scene *sc)
{
	__UINT8_TYPE__	i;
	int				y;
	pthread_t		tab[NB_TH];
	t_thread_data	thread_data[NB_TH];

	i = 0;
	y = 0;
	while (i < NB_TH)
	{
		thread_data[i].data = data;
		thread_data[i].sc = sc;
		thread_data[i].y_start = y;
		y += HEIGHT / NB_TH;
		y += (int []){0, 1}[i < HEIGHT % NB_TH];
		thread_data[i].y_end = y;
		if (pthread_create(tab + i, NULL, thread_rendering, thread_data + i))
			break ;
		i++;
	}
	//if (i < NB_TH)
		//err management
	i = 0;
	while (i < NB_TH)
		pthread_join(tab[i++], NULL);
}
