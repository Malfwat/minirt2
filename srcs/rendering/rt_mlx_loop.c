/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:14:30 by me                #+#    #+#             */
/*   Updated: 2026/11/21 00:14:59 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "mlx.h"

int	keyhook(int keycode, void *param)
{
	t_graphics	*data;

	data = param;
	if (keycode == ESC)
		mlx_loop_end(data->mlx);
	return (0);
}

int	stop_loop(void *param)
{
	mlx_loop_end(((t_graphics *)param)->mlx);
	return (0);
}
