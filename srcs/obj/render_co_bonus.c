/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_co_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 20:51:24 by me                #+#    #+#             */
/*   Updated: 2026/11/25 00:02:03 by me               ###   ########.fr       */
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

static bool	solve_co_lat(t_co_eq data, t_hit *tmp, double t)
{
	double	h;

	if (t < 1e-4)
		return (false);
	h = data.m + t * data.k;
	if (h > data.co->height || h < 0)
		return (false);
	if (tmp->t < t)
		return (false);
	tmp->t = t;
	tmp->p = add(data.cam_o, mult(data.ray_dir, tmp->t));
	tmp->normal = sub(mult(sub(tmp->p, data.co->coordinate),
				data.a), mult(data.co->vec, h));
	tmp->normal = normalize(tmp->normal);
	tmp->obj = data.co;
	return (true);
}

static bool	ray_cast_disk(t_co_eq *data, t_hit *hit, t_vec3	disk_o, double div)
{
	double	tmp;
	t_vec3	p;

	tmp = -scal(sub(data->cam_o, disk_o), data->co->vec) / div;
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
	t_vec3	o;
	double	denom;

	o = add(data->co->coordinate, mult(data->co->vec, data->co->height));
	denom = scal(data->ray_dir, data->co->vec);
	if (fabs(denom) < 1e-4)
		return (false);
	return (ray_cast_disk(data, hit, o, denom));
}

bool	co_hit(t_obj *co, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_co_eq	data;
	t_hit	tmp;
	bool	ret;

	data.q = co_quad(co, d, o, &data);
	data.ray_dir = d;
	data.cam_o = o;
	data.co = co;
	tmp.t = INFINITY;
	if (!quad(data.q, &data.s1, &data.s2))
		return (false);
	ret = false;
	if (solve_co_lat(data, &tmp, data.s1))
		ret = true;
	if (solve_co_lat(data, &tmp, data.s2))
		ret = true;
	if (solve_co_eq_disk(&data, &tmp))
		ret = true;
	if (!ret)
		return (false);
	*hit = tmp;
	return (true);
}
