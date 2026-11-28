/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_color_ops_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 01:38:28 by me                #+#    #+#             */
/*   Updated: 2026/11/28 01:20:50 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_color.h"
#include "rt_math.h"
#include "rt_render.h"
#include "rt_struct.h"

#include <math.h>

t_color_double	ppm_to_tcolor_double(t_ppm *tex, int x, int y)
{
	int				i;
	t_color_double	c;

	i = (tex->width * y + x) * 3;
	c = (t_color_double){tex->map[i], tex->map[i + 1], tex->map[i + 2]};
	return (c);
}

t_color	ppm_to_tcolor(t_ppm *tex, int x, int y)
{
	int		index;
	t_color	c;

	index = (tex->width * y + x) * 3;
	c = (t_color){tex->map[index], tex->map[index + 1], tex->map[index + 2]};
	return (c);
}

static t_color	texel_interpolate_color(t_ppm *tex, double x, double y)
{
	t_color_double	c;

	c = texel_interpolate(tex, x, y);
	return (cdouble_to_c(c, 1));
}

t_color	texture_color(t_hit hit, t_obj *obj, t_texel *pos)
{
	t_ppm	*tex;

	tex = obj->texture;
	if (obj->id == sphere)
		get_xy_sp(hit, obj, pos);
	else if (obj->id == cylinder)
		get_xy_cy(hit, obj, pos);
	else
		get_xy_pl(hit, obj, pos);
	pos->x *= (tex->width - 1);
	pos->y *= (tex->height - 1);
	if (pos->x == tex->width - 1 || pos->y == tex->height - 1)
		return (ppm_to_tcolor(tex, pos->x, pos->y));
	return (texel_interpolate_color(tex, pos->x, pos->y));
}
