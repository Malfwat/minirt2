/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:13:04 by me                #+#    #+#             */
/*   Updated: 2026/11/21 01:22:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"
#include "rt_graphics.h"

#include "mlx.h"

#include <stdlib.h>

void	destroy_graphics(t_graphics *data)
{
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
	}
	free(data->mlx);
}
