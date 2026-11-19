/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:31:59 by me                #+#    #+#             */
/*   Updated: 2026/11/19 01:49:11 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_struct.h"
#include "rt_graphics.h"

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

bool	sp_hit(t_obj *sp, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_quad	q;
	bool	ret;

	q = sp_quad(sp, d, o);
	ret = solve_hit(q, &hit->t);
	if (!ret)
		return (false);
	hit->p = mult(d, hit->t);
	hit->normal = normalize(sub(hit->p, sp->coordinate));
	hit->obj = sp;
	return (true);
}
