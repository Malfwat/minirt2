/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/16 14:33:50 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_thread_data
{
	t_graphics	*data;
	t_scene		*sc;
	int			y_start;
	int			y_end;
	//sem_t		*sem;
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
	__UINT8_TYPE__	nb_succeed;
	pthread_t		tab[NB_TH];
	t_thread_data	thread_data[NB_TH];


	i = 0;
	while (i < NB_TH)
	{
		thread_data[i].data = data;
		thread_data[i].sc = sc;
		thread_data[i].y_start = i * HEIGHT/NB_TH;
		thread_data[i].y_end = (i + 1) * HEIGHT/NB_TH;
		if (HEIGHT % NB_TH)
		{
			if (i < HEIGHT % NB_TH)
			{
				if (i != 0)
					thread_data[i].y_start += i;
				thread_data[i].y_end += i + 1;
			}
			else
			{
				thread_data[i].y_start += HEIGHT % NB_TH;
				thread_data[i].y_end += HEIGHT % NB_TH;
				if (thread_data[i].y_end > HEIGHT)
					thread_data[i].y_end = HEIGHT;
			}
		}
		if (pthread_create(tab + i, NULL, thread_rendering, thread_data + i))
		{
			//err management
			break ;
		}
		printf("start:%i\tend:%i\n", thread_data[i].y_start, thread_data[i].y_end);
		i++;
	}
	nb_succeed = i;
	i = 0;
	while (i < nb_succeed)
		pthread_join(tab[i++], NULL);
}
