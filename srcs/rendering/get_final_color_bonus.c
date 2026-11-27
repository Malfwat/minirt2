/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:33:47 by me                #+#    #+#             */
/*   Updated: 2026/11/27 03:27:18 by me               ###   ########.fr       */
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
	t_obj	local;
	t_texel	pos;

	local = *hit.obj;
	hit.obj = &local;
	if (hit.obj->texture)
		hit.obj->color = texture_color(hit, hit.obj, &pos);
	if (hit.obj->normals)
		hit.normal = normalize(texture_vec(hit.obj, &pos));
	if (hit.obj->checker_size)
		hit.obj->color = checker_color(hit, hit.obj);
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
