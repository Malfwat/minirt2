/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_co_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 20:51:24 by me                #+#    #+#             */
/*   Updated: 2026/11/24 22:01:23 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_element.h"
#include "rt_math.h"
#include "rt_struct.h"

t_quad	co_quad(t_obj *co, t_vec3 d, t_vec3 o, t_co_eq *data)
{
	t_quad	q;
	t_vec3	u;

	u = sub(o, co->coordinate);
	data->m = scal(u, co->vec);
	data->k = scal(d, co->vec);
	data->a = co->height;
	data->a = data->a * data->a;
	data->a /= data->a + (co->diameter / 2) * (co->diameter / 2);
	q.a = data->k * data->k - scal(d, d) * data->a;
	q.b = data->m * data->k - data->a * scal(u, d);
	q.b *= 2;
	q.c = data->m * data->m - data->a * scal(u, u);
	return (q);
}
