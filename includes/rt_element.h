/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_element.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:43:09 by me                #+#    #+#             */
/*   Updated: 2026/11/22 20:37:44 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ELEMENT_H
# define RT_ELEMENT_H

# include "rt_math.h"
# include "rt_struct.h"
# include "rt_graphics.h"

void		free_obj(t_obj *lst);
void		free_light(t_light *lst);

bool		cy_hit(t_obj *sp, t_vec3 d, t_vec3 o, t_hit *hit);
bool		pl_hit(t_obj *sp, t_vec3 d, t_vec3 o, t_hit *hit);
bool		sp_hit(t_obj *sp, t_vec3 d, t_vec3 o, t_hit *hit);

typedef bool	(*t_intersect)(t_obj *, t_vec3, t_vec3, t_hit *);

t_intersect	get_intersect_f(enum e_obj id);

typedef struct s_cy_eq
{
	double	s1;
	double	s2;
	double	m;
	double	k;
	t_quad	q;
	t_obj	*cy;
	t_vec3	cam_o;
	t_vec3	ray_dir;
}	t_cy_eq;

void		update_hit_lat_surface(t_cy_eq *data, t_hit *hit, double s);

#endif /*RT_ELEMENT_H*/