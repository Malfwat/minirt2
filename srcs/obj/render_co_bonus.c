/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_co_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 20:51:24 by me                #+#    #+#             */
/*   Updated: 2026/11/24 23:29:49 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_element.h"
#include "rt_math.h"
#include "rt_struct.h"
#include "rt_render.h"

#include <math.h>

t_quad	co_quad(t_obj *co, t_vec3 d, t_vec3 o, t_co_eq *data)
{
	t_quad	q;

	data->u = sub(o, co->coordinate);
	data->m = scal(data->u, co->vec);
	data->k = scal(d, co->vec);
	data->a = co->height * co->height;
	data->a /= data->a + (co->diameter / 2) * (co->diameter / 2);
	q.a = data->k * data->k - scal(d, d) * data->a;
	q.b = data->m * data->k - data->a * scal(data->u, d);
	q.b *= 2;
	q.c = data->m * data->m - data->a * scal(data->u, data->u);
	return (q);
}

bool	check_root(double t, t_co_eq data, t_hit *hit)
{
	double	h;

	if (t < 1e-4)
		return (false);
	h = data.m + t * data.k;
	if (h > data.co->height || h < 0)
		return (false);
	if (hit->t > t)
		hit->t = t;
	return (true);
}

static bool	ray_cast_disk(t_co_eq *data, t_hit *hit, t_vec3	disk_o, double denom)
{
	double	tmp;
	t_vec3	p;

	tmp = -scal(sub(data->cam_o, disk_o), data->co->vec) / denom;
	if (tmp < 1e-4)
		return (false);
	p = add(data->cam_o, mult(data->ray_dir, tmp));
	if (!(get_norme(sub(p, disk_o)) <= data->co->diameter / 2 && hit->t > tmp))
		return (false);
	hit->t = tmp;
	hit->p = p;
	hit->normal = data->co->vec;
	if (scal(sub(disk_o, data->co->coordinate), data->co->vec) < 0)
		hit->normal = mult(hit->normal, -1);
	hit->obj = data->co;
	return (true);
}


bool	solve_co_eq_disk(t_co_eq *data, t_hit *hit)
{
	bool	ret1;
	bool	ret2;
	t_vec3	o1;
	t_vec3	o2;
	double	denom;

	o1 = add(data->co->coordinate, mult(data->co->vec, data->co->height));
	o2 = sub(data->co->coordinate, mult(data->co->vec, data->co->height));
	denom = scal(data->ray_dir, data->co->vec);
	if (fabs(denom) < 1e-4)
		return (false);
	ret1 = ray_cast_disk(data, hit, o1, denom);
	ret2 = ray_cast_disk(data, hit, o2, denom);
	return (ret2 || ret1);
}

bool	co_hit(t_obj *co, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_co_eq	data;
	t_hit	tmp;
	double	h;
	bool	ret1;
	bool	ret2;
	bool	ret3;

	data.q = co_quad(co, d, o, &data);
	data.ray_dir = d;
	data.cam_o = o;
	data.co = co;
	tmp.t = INFINITY;
	if (!quad(data.q, &data.s1, &data.s2))
		return (false);
	ret1 = false;
	ret2 = false;
	ret3 = false;
	if (check_root(data.s1, data, &tmp))
		ret1 = true;
	if (check_root(data.s2, data, &tmp))
		ret2 = true;
	if (solve_co_eq_disk(&data, &tmp))
		ret3 = true;
	if (!ret1 && !ret2 && !ret3)
		return (false);
	hit->t = tmp.t;
	hit->obj = co;
	hit->p = add(o, mult(d, hit->t));
	h = data.m + data.k * hit->t;
	hit->normal = sub(mult(sub(hit->p, co->coordinate), data.a), mult(co->vec, h));
	hit->normal = normalize(hit->normal);
	return (true);
}
