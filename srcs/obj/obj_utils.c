/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/22 20:37:49 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_element.h"
#include "rt_error.h"
#include "rt_struct.h"
#include "str.h"

#include <stdlib.h>

void	free_obj(t_obj *lst)
{
	void	*ptr;

	while (lst)
	{
		ptr = lst;
		lst = lst->next;
		free(ptr);
	}
}

t_err	add_obj(t_scene *sc, t_obj o)
{
	t_obj	*node;

	node = malloc(sizeof(t_obj));
	if (!node)
		return (syscall_err);
	ft_memcpy(node, &o, sizeof(t_obj));
	node->next = sc->obj_lst;
	sc->obj_lst = node;
	return (ok);
}

t_intersect	get_intersect_f(enum e_obj id)
{
	if (id == sphere)
		return (sp_hit);
	if (id == plan)
		return (pl_hit);
	if (id == cylinder)
		return (cy_hit);
	return (NULL);
}

void	update_hit_lat_surface(t_cy_eq *data, t_hit *hit, double s)
{
	t_vec3	cp;

	hit->t = s;
	hit->p = add(data->cam_o, mult(data->ray_dir, hit->t));
	cp = sub(hit->p, data->cy->coordinate);
	hit->normal = normalize(sub(cp, mult(data->cy->vec,
					scal(cp, data->cy->vec))));
	hit->obj = data->cy;
}
