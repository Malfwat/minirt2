/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 22:21:54 by me                #+#    #+#             */
/*   Updated: 2026/11/19 02:04:18 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_math.h"
#include "rt_struct.h"
#include "rt_graphics.h"

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

static double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

t_color	get_final_color(t_scene *sc, t_hit hit, t_light *lights, t_light amb)
{
	t_vec3	l;
	t_color	a;
	t_color	b;
	t_color	tmp;
	bool	factor;

	a = mult_color_light(hit.obj->color, amb, 1);
	ft_bzero(&b, sizeof(b));
	while (lights)
	{
		l = sub(sc->light_lst->coordinate, hit.p);
		l = normalize(l);
		factor = max(0, scal(l, hit.normal));
		tmp = mult_color_light(hit.obj->color, *lights, factor);
		b = add_color(b, tmp);
		lights = lights->next;
	}
	return (add_color(a, b));
}
