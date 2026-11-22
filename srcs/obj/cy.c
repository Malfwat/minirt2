/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:17:07 by me                #+#    #+#             */
/*   Updated: 2026/11/22 20:38:54 by me               ###   ########.fr       */
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

bool	ray_cast_disk(t_cy_eq *data, t_hit *hit, t_vec3	disk_o, double denom)
{
	double	tmp;
	t_vec3	p;

	tmp = -scal(sub(data->cam_o, disk_o), data->cy->vec) / denom;
	if (tmp < 1e-4)
		return (false);
	p = add(data->cam_o, mult(data->ray_dir, tmp));
	if (!(get_norme(sub(p, disk_o)) <= data->cy->diameter / 2 && hit->t > tmp))
		return (false);
	hit->t = tmp;
	hit->p = p;
	hit->normal = data->cy->vec;
	if (scal(sub(disk_o, data->cy->coordinate), data->cy->vec) < 0)
		hit->normal = mult(hit->normal, -1);
	hit->obj = data->cy;
	return (true);
}

bool	solve_cy_eq_disk(t_cy_eq *data, t_hit *hit)
{
	bool	ret1;
	bool	ret2;
	t_vec3	o1;
	t_vec3	o2;
	double	denom;

	o1 = add(data->cy->coordinate, mult(data->cy->vec, data->cy->height / 2));
	o2 = sub(data->cy->coordinate, mult(data->cy->vec, data->cy->height / 2));
	denom = scal(data->ray_dir, data->cy->vec);
	if (fabs(denom) < 1e-4)
		return (false);
	ret1 = ray_cast_disk(data, hit, o1, denom);
	ret2 = ray_cast_disk(data, hit, o2, denom);
	return (ret2 || ret1);
}

bool	solve_cy_eq_lat_surface(t_cy_eq *data, t_hit *hit)
{
	double	h1;
	double	h2;
	bool	ret;

	ret = false;
	h1 = data->m + data->s1 * data->k;
	h2 = data->m + data->s2 * data->k;
	if (data->s1 > 1e-4 && fabs(h1) < data->cy->height / 2 && hit->t > data->s1)
	{
		update_hit_lat_surface(data, hit, data->s1);
		ret = true;
	}
	if (data->s2 > 1e-4 && fabs(h2) < data->cy->height / 2 && hit->t > data->s2)
	{
		update_hit_lat_surface(data, hit, data->s2);
		ret = true;
	}
	return (ret);
}

bool	cy_hit(t_obj *cy, t_vec3 d, t_vec3 o, t_hit *hit)
{
	bool	ret1;
	bool	ret2;
	t_cy_eq	data;
	t_hit	tmp;

	data.q = cy_quad(cy, d, o, &data);
	data.ray_dir = d;
	data.cam_o = o;
	data.cy = cy;
	tmp.t = INFINITY;
	ret2 = false;
	ret1 = solve_cy_eq_disk(&data, &tmp);
	if (quad(data.q, &data.s1, &data.s2))
		ret2 = solve_cy_eq_lat_surface(&data, &tmp);
	if (!ret1 && !ret2)
		return (false);
	*hit = tmp;
	return (true);
}
