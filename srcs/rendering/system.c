/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:52:40 by me                #+#    #+#             */
/*   Updated: 2026/11/18 14:32:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_math.h"
#include "str.h"

#include <math.h>

t_axes	get_system(t_vec3 z)
{
	t_axes	axe;
	t_vec3	tmp;
	
	z = normalize(z);
	ft_bzero(&tmp, sizeof(tmp));
	if (fabs(z.y) > 0.95)
		tmp.x = 1;
	else
		tmp.y = 1;
	axe.z = z;
	axe.x = cross(axe.z, tmp);
	axe.y = cross(axe.x, axe.z);
	return (axe);
}
