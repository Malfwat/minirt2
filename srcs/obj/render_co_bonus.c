/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_co_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 20:51:24 by me                #+#    #+#             */
/*   Updated: 2026/11/24 22:31:21 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_element.h"
#include "rt_math.h"
#include "rt_struct.h"

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

bool	co_hit(t_obj *co, t_vec3 d, t_vec3 o, t_hit *hit)
{
	t_co_eq	data;
	t_hit	tmp;
	double	h1;
	double	h2;
	double	res;

	data.q = co_quad(co, d, o, &data);
	data.ray_dir = d;
	data.cam_o = o;
	data.co = co;
	tmp.t = INFINITY;
	if (!quad(data.q, &data.s1, &data.s2))
		return (false);
	h1 = data.m + data.s1 * data.k;
	h2 = data.m + data.s1 * data.k;
	res = min(h1, h2);
	if (res > co->height)
		return (false);
	hit->obj = co;
	if (h1 == res)
		hit->t = data.s1;
	else
		hit->t = data.s2;
	hit->p = add(o, mult(d, hit->t));
	hit->normal = (t_vec3){0, 0, 0};
	return (true);
}
