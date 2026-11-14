/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 21:50:59 by me                #+#    #+#             */
/*   Updated: 2026/11/14 22:26:42 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"

#include <math.h>

double	get_norme(t_vec3 vec)
{
	double	tmp;

	tmp = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (sqrt(tmp));
}

t_vec3	normalize(t_vec3 vec)
{
	double	norme;

	norme = get_norme(vec);
	vec.x /= norme;
	vec.y /= norme;
	vec.z /= norme;
	return (vec);
}
