/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:19:48 by me                #+#    #+#             */
/*   Updated: 2026/11/22 16:43:52 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_graphics.h"
#include "rt_graphics_bonus.h"

#include <errno.h>
#include <pthread.h>

static t_thread_data	attrib_data(t_render *params, int i, int b[])
{
	t_thread_data	tmp;

	tmp.b2 = b[0];
	tmp.b3 = b[1];
	tmp.b4 = b[2];
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
	int		i;
	t_err	err;
	int		b[3];

	i = -1;
	fill_bases(b);
	while (++i < NB_TH)
	{
		param->th_data[i] = attrib_data(param, i, b);
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
