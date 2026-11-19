/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:17:07 by me                #+#    #+#             */
/*   Updated: 2026/11/19 15:59:28 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_element.h"
#include "rt_math.h"
#include "rt_struct.h"
#include "rt_graphics.h"

#include <math.h>

t_quad	cy_quad(t_obj *cy, t_vec3 d, t_vec3 o, t_cy_eq *data)
{
	t_quad	q;
	t_vec3	x;
	t_vec3	y;

	data->k = scal(d, cy->vec);
	data->m = scal(sub(o, cy->coordinate), cy->vec);
	x = sub(d, mult(cy->vec, data->k));
	y = sub(sub(o, cy->coordinate), mult(cy->vec, data->m));
	q.a = scal(x, x);
	q.b = 2 * scal(y, x);
	q.c = scal(y, y) - (cy->diameter / 2) * (cy->diameter / 2);
	return (q);
}

bool	solve_cy_eq(t_cy_eq *data, double s1, double s2, double *t)
{
	double	h1;
	double	h2;

	h1 = data->m + s1 * data->k;
	h2 = data->m + s2 * data->k;
	if (s1 > 1e-4)
	{
		if (fabs(h1) < data->cy->height / 2)
		{
			*t = h1;
			return (true);
		}
	}
	if (s2 > 1e-4)
	{
		if (fabs(h2) < data->cy->height / 2)
		{
			*t = h2;
			return (true);
		}
	}
	return (false);
}

bool	cy_hit(t_obj *cy, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_vec3	cp;
	t_cy_eq	data;
	double	s1;
	double	s2;

	data.q = cy_quad(cy, d, o, &data);
	if (!quad(data.q, &s1, &s2))
		return (false);
	data.cy = cy;
	if (!solve_cy_eq(&data, s1, s2, &hit->t))
		return (false);
	hit->p = add(o, mult(d, hit->t));
	cp = sub(hit->p, cy->coordinate);
	hit->normal = normalize(sub(cp, mult(cy->vec, scal(cp, cy->vec))));
	hit->obj = cy;
	return (true);
}
