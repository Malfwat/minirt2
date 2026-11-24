/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 22:21:54 by me                #+#    #+#             */
/*   Updated: 2026/11/24 13:25:08 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_config.h"
#include "rt_render.h"
#include "rt_struct.h"

int	t_color_to_int(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

t_color	mult_color_light(t_color a, t_light light, double factor)
{
	t_color	c;

	c.r = a.r * (light.color.r / 255.0) * light.ratio * factor;
	c.g = a.g * (light.color.g / 255.0) * light.ratio * factor;
	c.b = a.b * (light.color.b / 255.0) * light.ratio * factor;
	return (c);
}

t_color	add_color(t_color a, t_color b)
{
	t_color	c;
	int		tmp;

	tmp = a.r + b.r;
	if (tmp > 255)
		tmp = 255;
	c.r = tmp;
	tmp = a.g + b.g;
	if (tmp > 255)
		tmp = 255;
	c.g = tmp;
	tmp = a.b + b.b;
	if (tmp > 255)
		tmp = 255;
	c.b = tmp;
	return (c);
}

t_color	checker_color(t_hit hit, t_obj *obj)
{
	double	u;
	double	v;
	t_color	c;
	t_axes	hit_axes;

	hit_axes = get_system(hit.normal);
	u = scal(sub(hit.p, obj->coordinate), hit_axes.x) / obj->checker_size;
	v = scal(sub(hit.p, obj->coordinate), hit_axes.y) / obj->checker_size;
	c = obj->color;
	if ((int)(floor(u) + floor(v)) % 2 != 0)
		return ((t_color){c.r * DARKEN, c.g * DARKEN, c.b * DARKEN});
	return (c);
}

t_color	get_final_color(t_hit hit, t_scene *sc)
{
	t_light	*l;
	t_color	a;
	t_color	b;
	t_obj	local;

	if (hit.obj->checker_size)
	{
		local = *hit.obj;
		hit.obj = &local;
		hit.obj->color = checker_color(hit, hit.obj);
	}
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
