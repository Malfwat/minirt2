/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:17:07 by me                #+#    #+#             */
/*   Updated: 2026/11/19 11:46:50 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_struct.h"
#include "rt_graphics.h"

t_quad	cy_quad(t_obj *cy, t_vec3 d, t_vec3 o)
{
	t_quad	q;
	double	k;
	double	m;
	t_vec3	x;
	t_vec3	y;

	k = scal(d, cy->vec);
	m = scal(sub(o, cy->coordinate), cy->vec);
	x = sub(d, mult(cy->vec, k));
	y = sub(sub(o, cy->coordinate), mult(cy->vec, m));
	q.a = scal(x, x);
	q.b = 2 * scal(y, x);
	q.c = scal(y, y) - (cy->diameter / 2) * (cy->diameter / 2);
	return (q);
}

bool	cy_hit(t_obj *cy, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_vec3	cp;
	t_quad	q;
	bool	ret;

	q = cy_quad(cy, d, o);
	ret = solve_hit(q, &hit->t);
	if (!ret)
		return (false);
	if (hit->t > cy->height / 2)
		return (false);
	hit->p = add(o, mult(d, hit->t));
	cp = sub(hit->p, cy->coordinate);
	hit->normal = normalize(sub(cp, mult(cy->vec, scal(cp, cy->vec))));
	hit->obj = cy;
	return (true);
}
