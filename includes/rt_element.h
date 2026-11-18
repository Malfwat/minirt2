/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_element.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:43:09 by me                #+#    #+#             */
/*   Updated: 2026/11/18 23:21:13 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ELEMENT_H
# define RT_ELEMENT_H

# include "rt_math.h"
# include "rt_struct.h"

void		free_obj(t_obj *lst);
void		free_light(t_light *lst);

t_quad		cy_quad(t_obj *sp, t_vec3 d, t_vec3 o);
t_quad		pl_quad(t_obj *sp, t_vec3 d, t_vec3 o);
t_quad		sp_quad(t_obj *sp, t_vec3 d, t_vec3 o);

typedef t_quad	(*t_get_quad)(t_obj *, t_vec3, t_vec3);

t_get_quad	fill_quad(enum e_obj id);

#endif /*RT_ELEMENT_H*/