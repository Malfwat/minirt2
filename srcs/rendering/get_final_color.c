/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:30:20 by me                #+#    #+#             */
/*   Updated: 2026/11/24 16:36:29 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_render.h"
#include "rt_color.h"
#include "str.h"

t_color	get_final_color(t_hit hit, t_scene *sc)
{
	t_light	*l;
	t_color	a;
	t_color	b;

	a = mult_color_light(hit.obj->color, sc->amb, 1);
	ft_bzero(&b, sizeof(b));
	l = sc->light_lst;
	while (l)
	{
		b = add_color(b, get_pixel_illumination(hit, l, sc));
		l = l->next;
	}
	return (add_color(a, b));
}
