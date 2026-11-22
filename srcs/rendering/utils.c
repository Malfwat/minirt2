/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 18:27:16 by me                #+#    #+#             */
/*   Updated: 2026/11/22 19:51:59 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt_graphics.h"

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

int	ligne(int cursor, int b2, int b3, int b4)
{
	if (cursor < b2)
		return (8 * cursor);
	else if (cursor < b3)
		return (8 * (cursor - b2) + 4);
	else if (cursor < b4)
		return (4 * (cursor - b3) + 2);
	return (2 * (cursor - b4) + 1);
}

void	fill_bases(int b[])
{
	int	c1;
	int	c2;
	int	c3;

	c1 = (HEIGHT + 7) / 8;
	c2 = (HEIGHT + 3) / 8;
	c3 = (HEIGHT + 1) / 4;
	b[0] = c1;
	b[1] = b[0] + c2;
	b[2] = b[1] + c3;
}

bool	delayed(t_time n, t_time l, long t)
{
	long	delay;

	delay = n.tv_sec * 1000000 + n.tv_usec;
	delay = delay - l.tv_sec * 1000000 - l.tv_usec;
	return (delay > t);
}
