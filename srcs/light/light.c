/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/19 02:44:09 by me               ###   ########.fr       */
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

bool	is_illuminated(t_hit hit, t_light light, t_hit *data)
{
	t_vec3	vec;
	t_vec3	p_offset;
	double	t_l;

	vec = sub(light.coordinate, hit.p);
	t_l = get_norme(vec);
	vec = normalize(vec);
	p_offset = add(hit.p, mult(vec, 1e-3));
	if (!get_intersect_f(hit.obj->id)(hit.obj, vec, p_offset, data))
		return (true);
	if (data->t < t_l)
		return (false);
	return (true);
}
