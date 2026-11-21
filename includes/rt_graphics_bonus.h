/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:21:19 by me                #+#    #+#             */
/*   Updated: 2026/11/21 03:00:27 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GRAPHICS_BONUS_H
# define RT_GRAPHICS_BONUS_H

# include "rt_graphics.h"
# include "rt_struct.h"

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# ifndef NB_TH
#  define NB_TH 8
# endif /*NB_TH*/

typedef struct s_band
{
	int				y_start;
	int				y_end;

	struct s_band	*next;
}	t_band;

typedef struct s_thread_data
{
	int			id;
	t_graphics	*data;
	t_scene		*sc;
	sem_t		*sem_stop;
	sem_t		*sem_printing;
	bool		*stop;
	int			y_start;
	int			y_end;
}	t_thread_data;

typedef struct timeval	t_time;

typedef struct s_render
{
	t_time			last;
	t_err			err;
	t_scene			sc;
	t_graphics		data;
	sem_t			sem_stop;
	sem_t			sem_printing[NB_TH];
	bool			stop;
	pthread_t		tab[NB_TH];
	t_thread_data	th_data[NB_TH];
}	t_render;

void	stop_and_join_thread(sem_t *sem, bool *stop, pthread_t tab[], int n);

t_err	render_th(t_render *param);
int		rendering_loop(void *param);
void	sem_n_post(sem_t *s, int n);
void	sem_n_wait(sem_t *s, int n);

#endif /*RT_GRAPHICS_BONUS_H*/