/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_element.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:43:09 by me                #+#    #+#             */
/*   Updated: 2026/11/19 00:13:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ELEMENT_H
# define RT_ELEMENT_H

# include "rt_math.h"
# include "rt_struct.h"

void		free_obj(t_obj *lst);
void		free_light(t_light *lst);

bool		cy_hit(t_obj *sp, t_vec3 d, t_vec3 o, double *t);
bool		pl_hit(t_obj *sp, t_vec3 d, t_vec3 o, double *t);
bool		sp_hit(t_obj *sp, t_vec3 d, t_vec3 o, double *t);

typedef bool	(*t_intersect)(t_obj *, t_vec3, t_vec3, double *);

t_intersect	get_intersect_f(enum e_obj id);

#endif /*RT_ELEMENT_H*/