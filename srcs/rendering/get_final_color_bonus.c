/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:33:47 by me                #+#    #+#             */
/*   Updated: 2026/11/27 18:52:10 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_render.h"
#include "rt_color.h"
#include "str.h"

void	texturize(t_hit *hit)
{
	t_texel	pos;
	t_vec3	n;
	t_vec3	t;
	t_vec3	b;
	t_vec3	tmp;

	if (hit->obj->texture)
		hit->obj->color = texture_color(*hit, hit->obj, &pos);
	if (hit->obj->normals)
	{
		n = hit->normal;
		t = pos.axes.x;
		b = mult(pos.axes.y, -1);
		hit->normal = normalize(texture_vec(hit->obj, &pos));
		tmp = add(mult(t, hit->normal.x), mult(b, hit->normal.y));
		hit->normal = add(tmp, mult(n, hit->normal.z));
		hit->normal = normalize(hit->normal);
	}
	if (hit->obj->checker_size)
		hit->obj->color = checker_color(*hit, hit->obj);
}

t_color	get_final_color(t_hit hit, t_scene *sc)
{
	t_light	*l;
	t_color	a;
	t_color	b;
	t_obj	local;

	local = *hit.obj;
	hit.obj = &local;
	texturize(&hit);
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
