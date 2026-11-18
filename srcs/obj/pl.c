/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 23:17:07 by me                #+#    #+#             */
/*   Updated: 2026/11/19 00:20:10 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_struct.h"

#include <math.h>

bool	pl_hit(t_obj *pl, t_vec3 d, t_vec3 o, double *t)
{
	double	denom;

	denom = scal(d, pl->vec);
	if (fabs(denom) < 1e-4)
		return (false);
	*t = -scal(sub(o, pl->coordinate), pl->vec) / denom;
	return (true);
}
