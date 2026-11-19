/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:17:07 by me                #+#    #+#             */
/*   Updated: 2026/11/19 17:25:15 by me               ###   ########.fr       */
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

bool	solve_cy_eq_disk(t_cy_eq *data, t_vec3 o, t_hit *hit)
{
	t_vec3	o1;
	t_vec3	o2;
	t_vec3	p;
	double	denom;
	double	tmp;

	data->cy->vec = normalize(data->cy->vec);
	o1 = add(data->cy->coordinate, mult(data->cy->vec, data->cy->height / 2));
	o2 = sub(data->cy->coordinate, mult(data->cy->vec, data->cy->height / 2));
	denom = scal(data->ray_dir, data->cy->vec);
	if (fabs(denom) < 1e-4)
		return (false);
	tmp = -scal(sub(o, o1), data->cy->vec) / denom;
	if (tmp > 1e-4)
	{
		p = add(o, mult(data->ray_dir, tmp));
		if (get_norme(sub(p, o1)) <= data->cy->diameter / 2 && hit->t > tmp)
		{
			hit->t = tmp;
			hit->p = p;
			hit->normal = data->cy->vec;
			hit->obj = data-> cy;
			return (true);
		}
	}
	tmp = -scal(sub(o, o2), data->cy->vec) / denom;
	if (tmp > 1e-4)
	{
		p = add(o, mult(data->ray_dir, tmp));
		if (get_norme(sub(p, o2)) <= data->cy->diameter / 2 && hit->t > tmp)
		{
			hit->t = tmp;
			hit->p = p;
			hit->normal = data->cy->vec;
			hit->obj = data-> cy;
			return (true);
		}
	}
	return (false);
}

bool	solve_cy_eq_pipe(t_cy_eq *data, double s1, double s2, t_hit *hit)
{
	t_vec3	cp;
	double	h1;
	double	h2;
	bool	ret;

	ret = false;
	h1 = data->m + s1 * data->k;
	h2 = data->m + s2 * data->k;
	if (s1 > 1e-4 && fabs(h1) < data->cy->height / 2 && hit->t > s1)
	{
		hit->t = s1;
		hit->p = add(data->cam_o, mult(data->ray_dir, hit->t));
		cp = sub(hit->p, data->cy->coordinate);
		hit->normal = normalize(sub(cp, mult(data->cy->vec,
						scal(cp, data->cy->vec))));
		hit->obj = data->cy;
		ret = true;
	}
	if (s2 > 1e-4 && fabs(h2) < data->cy->height / 2 && hit->t > s2)
	{
		hit->t = s2;
		hit->p = add(data->cam_o, mult(data->ray_dir, hit->t));
		cp = sub(hit->p, data->cy->coordinate);
		hit->normal = normalize(sub(cp, mult(data->cy->vec,
						scal(cp, data->cy->vec))));
		hit->obj = data->cy;
		ret = true;
	}
	return (ret);
}

bool	cy_hit(t_obj *cy, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_cy_eq	data;
	double	s1;
	double	s2;
	t_hit	tmp;

	data.q = cy_quad(cy, d, o, &data);
	if (!quad(data.q, &s1, &s2))
		return (false);
	data.ray_dir = d;
	data.cam_o = o;
	data.cy = cy;
	tmp.t = INFINITY;
	if (!solve_cy_eq_disk(&data, o, &tmp)
		&& !solve_cy_eq_pipe(&data, s1, s2, &tmp))
		return (false);
	*hit = tmp;
	return (true);
}
