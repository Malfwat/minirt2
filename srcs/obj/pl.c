/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:17:07 by me                #+#    #+#             */
/*   Updated: 2026/11/19 01:47:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_struct.h"
#include "rt_graphics.h"

#include <math.h>

bool	pl_hit(t_obj *pl, t_vec3 d, t_vec3 o, t_hit *hit)
{
	double	denom;

	denom = scal(d, pl->vec);
	if (fabs(denom) < 1e-4)
		return (false);
	hit->t = -scal(sub(o, pl->coordinate), pl->vec) / denom;
	hit->p = mult(d, hit->t);
	hit->normal = pl->vec;
	hit->obj = pl;
	return (true);
}
