/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 22:21:54 by me                #+#    #+#             */
/*   Updated: 2026/11/19 01:17:42 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"

int	t_color_to_int(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

t_color	mult_color_light(t_color a, t_light light, double x)
{
	t_color	c;

	c.r = a.r * (light.color.r / 255.0) * light.ratio * x;
	c.g = a.g * (light.color.g / 255.0) * light.ratio * x;
	c.b = a.b * (light.color.b / 255.0) * light.ratio * x;
	return (c);
}
