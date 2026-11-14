/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:47:55 by me                #+#    #+#             */
/*   Updated: 2026/11/14 21:06:41 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"

void	put_pxl(int	x, int y, t_graphics *data, int color)
{
	void	*dst;

	dst = data->image.addr
		+ (y * data->image.line_length
		+ x * (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_line(int y_start, int y_end, t_graphics *data)
{
	int	i;

	i = 0;
	while (y_start < y_end)
	{
		i = 0;
		while (i < WIDTH)
		{
			put_pxl(i, y_start, data, 0x00ff0000);
			i++;
		}
		y_start++;
	}
}