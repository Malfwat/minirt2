/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrant_diff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 00:32:20 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:28:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_color.h"

static double	quad_max(double a, double b, double c, double d)
{
	double	x;
	double	y;

	x = max(a, b);
	y = max(c, d);
	return (max(x, y));
}

static double	quad_min(double a, double b, double c, double d)
{
	double	x;
	double	y;

	x = min(a, b);
	y = min(c, d);
	return (min(x, y));
}

double	quadrant_diff(t_quadrant q)
{
	double	tab[3];
	double	x;
	double	y;

	x = quad_max(q.colors[0].r, q.colors[1].r, q.colors[2].r, q.colors[3].r);
	y = quad_min(q.colors[0].r, q.colors[1].r, q.colors[2].r, q.colors[3].r);
	tab[0] = x - y;
	x = quad_max(q.colors[0].g, q.colors[1].g, q.colors[2].g, q.colors[3].g);
	y = quad_min(q.colors[0].g, q.colors[1].g, q.colors[2].g, q.colors[3].g);
	tab[1] = x - y;
	x = quad_max(q.colors[0].b, q.colors[1].b, q.colors[2].b, q.colors[3].b);
	y = quad_min(q.colors[0].b, q.colors[1].b, q.colors[2].b, q.colors[3].b);
	tab[2] = x - y;
	return (quad_max(tab[0], tab[1], tab[2], 0));
}
