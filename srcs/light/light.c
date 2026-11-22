/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:16:43 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_render.h"
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

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_pxl_data	get_pixel_light_factor(t_scene *sc, t_hit hit, t_cast data)
{
	t_vec3		tmp;
	t_pxl_data	factors;

	tmp = normalize(sub(sc->cam.coordinate, hit.p));
	tmp = normalize(add(data.dir, tmp));
	factors.dif = max(0, scal(data.dir, hit.normal));
	factors.spec = pow(max(0, scal(hit.normal, tmp)), hit.obj->exposant);
	factors.spec *= hit.obj->intensity;
	return (factors);
}

t_color	get_pixel_illumination(t_hit hit, t_light *l, t_scene *sc)
{
	t_cast		data;
	t_hit		h;
	t_pxl_data	pxl_data;

	data.dir = sub(l->coordinate, hit.p);
	data.lim = get_norme(data.dir);
	data.dir = normalize(data.dir);
	data.origin = add(hit.p, mult(data.dir, 1e-4));
	ft_bzero(&h, sizeof(h));
	ft_bzero(&pxl_data, sizeof(pxl_data));
	if (!cast_ray(sc, data, &h))
		pxl_data = get_pixel_light_factor(sc, hit, data);
	pxl_data.c_spec = (t_color){255, 255, 255};
	if (!hit.obj->intensity || !hit.obj->exposant)
		return (mult_color_light(hit.obj->color, *l, pxl_data.dif));
	pxl_data.c_dif = mult_color_light(hit.obj->color, *l, pxl_data.dif);
	pxl_data.c_spec = mult_color_light(pxl_data.c_spec, *l, pxl_data.spec);
	return (add_color(pxl_data.c_dif, pxl_data.c_spec));
}
