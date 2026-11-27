/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:33:47 by me                #+#    #+#             */
/*   Updated: 2026/11/27 01:19:21 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_render.h"
#include "rt_color.h"
#include "rt_math.h"
#include "str.h"

t_color	ppm_to_tcolor(t_ppm *tex, int x, int y)
{
	int		index;
	t_color	c;

	index = (tex->width * y + x) * 3;
	c = (t_color){tex->map[index], tex->map[index + 1], tex->map[index + 2]};
	return (c);
}

static void	get_uv_sp(t_hit hit, t_obj *obj, double *u, double *v)
{
	double	pol;
	double	azim;
	t_vec3	d;

	d = sub(hit.p, obj->coordinate);
	pol = acos(d.y / (obj->diameter / 2));
	azim = atan2(d.z, d.x);
	*u = (azim + M_PI) / (2 * M_PI);
	*v = pol / M_PI;
}

t_color	texel_interpolate(t_ppm *tex, double x, double y)
{
	double	fx;
	double	fy;
	t_color	c;
	t_color	tmp;

	fx = x - (int)x;
	fy = y - (int)y;
	c = ppm_to_tcolor(tex, (int)x, (int)y);
	c = mult_color_ratio(c, (1 - fx) * (1 - fy));
	tmp = ppm_to_tcolor(tex, (int)x + 1, (int)y);
	tmp = mult_color_ratio(tmp, fx * (1 - fy));
	c = add_color(c, tmp);
	tmp = ppm_to_tcolor(tex, (int)x, (int)y + 1);
	tmp = mult_color_ratio(tmp, (1 - fx) * fy);
	c = add_color(c, tmp);
	tmp = ppm_to_tcolor(tex, (int)x + 1, (int)y + 1);
	tmp = mult_color_ratio(tmp, fx * fy);
	c = add_color(c, tmp);
	return (c);
}

t_color	texture_color(t_hit hit, t_obj *obj)
{
	double	x;
	double	y;

	if (1 - fabs(scal(hit.normal, obj->vec)) < 1e-3)
		return (obj->color);
	get_uv_sp(hit, obj, &x, &y);
	x *= (obj->texture->width - 1);
	y *= (obj->texture->height - 1);
	return (texel_interpolate(obj->texture, x, y));
}

t_color	get_final_color(t_hit hit, t_scene *sc)
{
	t_light	*l;
	t_color	a;
	t_color	b;
	t_obj	local;

	local = *hit.obj;
	hit.obj = &local;
	if (hit.obj->texture)
		hit.obj->color = texture_color(hit, hit.obj);
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
