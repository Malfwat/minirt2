/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/19 03:59:46 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_element.h"
#include "rt_graphics.h"
#include "rt_struct.h"
#include "str.h"

#include <stdlib.h>
#include <stdbool.h>

void	free_light(t_light *lst)
{
	void	*ptr;

	while (lst)
	{
		ptr = lst;
		lst = lst->next;
		free(ptr);
	}
}

bool	add_light(t_light **head, t_light data)
{
	t_light	*node;

	node = malloc(sizeof(t_light));
	if (!node)
		return (false);
	ft_memcpy(node, &data, sizeof(t_light));
	node->next = *head;
	*head = node;
	return (true);
}

bool	is_illuminated(t_hit hit, t_light light, t_obj *obj)
{
	t_hit	data;
	t_vec3	vec;
	t_vec3	p_offset;
	double	t_l;

	vec = sub(light.coordinate, hit.p);
	t_l = get_norme(vec);
	vec = normalize(vec);
	p_offset = add(hit.p, mult(vec, 1e-3));
	if (!get_intersect_f(obj->id)(obj, vec, p_offset, &data))
		return (true);
	if (data.t < t_l)
		return (false);
	return (true);
}

static double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_color	get_pixel_illumination(t_hit hit, t_light *l, t_scene *sc)
{
	t_cast	data;
	double	factor;
	t_hit	h;

	data.dir = sub(l->coordinate, hit.p);
	data.lim = get_norme(data.dir);
	data.dir = normalize(data.dir);
	data.origin = add(hit.p, mult(data.dir, 1e-4));
	factor = 0;
	ft_bzero(&h, sizeof(h));
	if (!cast_ray(sc, data, &h))
		factor = max(0, scal(data.dir, hit.normal));
	return (mult_color_light(hit.obj->color, *l, factor));
}
