/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_thread_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:05:34 by me                #+#    #+#             */
/*   Updated: 2026/11/21 01:58:05 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_THREAD_BONUS_H
# define RT_THREAD_BONUS_H

# include "rt_graphics.h"

# include <semaphore.h>

typedef struct s_thread_data
{
	t_graphics	*data;
	t_scene		*sc;
	sem_t		*sem_stop;
	sem_t		*sem_printing;
	bool		*stop;
	int			y_start;
	int			y_end;
}	t_thread_data;

struct	s_multi_threading
{
	int		err;
	int		lim;
	bool	stop;
	sem_t	sem;
};

#endif /*RT_THREAD_BONUS_H*/