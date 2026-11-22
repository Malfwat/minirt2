/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:03:21 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/22 16:55:57 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt_struct.h"
# include "rt_graphics.h"

void	free_scene(t_scene *sc);

# define USAGE "Error:\n\t./miniRT<_bonus> scene.rt\n"

typedef struct s_rt
{
	bool		stop;
	t_scene		sc;
	t_graphics	data;
}	t_rt;

#endif /* RT_H */