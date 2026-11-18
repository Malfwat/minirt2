/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:31:59 by me                #+#    #+#             */
/*   Updated: 2026/11/19 00:13:32 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_struct.h"

t_quad	sp_quad(t_obj *sp, t_vec3 d, t_vec3 o)
{
	t_quad	q;
	double	r;
	t_vec3	oc;

	oc = sub(o, sp->coordinate);
	q.a = scal(d, d);
	q.b = 2 * scal(d, oc);
	r = sp->diameter / 2;
	q.c = scal(oc, oc) - r * r;
	return (q);
}

bool	sp_hit(t_obj *sp, t_vec3 d, t_vec3 o, double *t)
{
	t_quad	q;

	q = sp_quad(sp, d, o);
	return (solve_hit(q, t));
}
