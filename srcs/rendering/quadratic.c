/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:57:25 by me                #+#    #+#             */
/*   Updated: 2026/11/22 20:30:58 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_math.h"

#include <math.h>

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

static bool	min_pos(double a, double b, double *t)
{
	if (a <= 0 && b <= 0)
		return (false);
	if (a <= 0)
		*t = b;
	else if (b <= 0)
		*t = a;
	else
		*t = min(a, b);
	return (true);
}

bool	quad(t_quad q, double *s1, double *s2)
{
	double	delt;

	delt = q.b * q.b - 4 * q.a * q.c;
	if (delt < 0 || !q.a)
		return (false);
	if (delt == 0)
	{
		*s1 = -q.b / (2 * q.a);
		*s2 = -q.b / (2 * q.a);
		return (true);
	}
	*s1 = (-q.b - sqrt(delt)) / (2 * q.a);
	*s2 = (-q.b + sqrt(delt)) / (2 * q.a);
	return (true);
}

bool	solve_hit(t_quad q, double *t)
{
	double	s1;
	double	s2;

	if (!quad(q, &s1, &s2))
		return (false);
	if (!min_pos(s1, s2, t))
		return (false);
	return (true);
}
