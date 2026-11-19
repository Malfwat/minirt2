/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/19 22:29:15 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
//#include "rt_element.h"
#include "rt_graphics.h"
#include "rt_struct.h"
#include "str.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

static double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_color	get_pixel_illumination(t_hit hit, t_light *l, t_scene *sc)
{
	t_cast	data;
	t_hit	h;

	data.dir = sub(l->coordinate, hit.p);
	data.lim = get_norme(data.dir);
	data.dir = normalize(data.dir);
	data.origin = add(hit.p, mult(data.dir, 1e-4));
	ft_bzero(&h, sizeof(h));
	double	dif = 0;
	double	spec = 0;
	if (!cast_ray(sc, data, &h))
	{
		t_vec3	tmp;

		tmp = normalize(sub(sc->cam.coordinate, hit.p));
		tmp = normalize(add(data.dir, tmp));
		dif = max(0, scal(data.dir, hit.normal));
		spec = pow(max(0, scal(hit.normal, tmp)), hit.obj->exposant) * hit.obj->intensity;
	}

	if (!hit.obj->intensity || !hit.obj->exposant)
		return (mult_color_light(hit.obj->color, *l, dif));

	t_color c = mult_color_light(hit.obj->color, *l, dif);
	t_color c2 = mult_color_light((t_color){255, 255, 255}, *l, spec);
	return (add_color(c, c2));
}
