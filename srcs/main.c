/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/11/14 19:05:35 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"
#include "rt_graphics.h"

#include "mlx.h"

#include <stdlib.h>

void	free_mlx(t_graphics *data)
{
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	destroy_graphics(t_graphics *data)
{
	mlx_destroy_image(data->mlx, data->image.img);
	mlx_destroy_window(data->mlx, data->win);
}

int	keyhook(int keycode, void *param)
{
	t_graphics	*data;

	data = param;
	if (keycode == ESC)
		mlx_loop_end(data->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_graphics	data;
	t_scene		sc;

	ft_bzero(&sc, sizeof(t_scene));
	ft_bzero(&data, sizeof(t_graphics));
	if (ac != 2)
		return (0);
	parse(av[1], &sc);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free_scene(&sc), 1);
	data.win = mlx_new_window(data.mlx, 500, 500, "Hello World!");
	if (!data.win)
		return (free_mlx(&data), free_scene(&sc), 1);
	mlx_key_hook(data.win, keyhook, &data);
	data.image.img = mlx_new_image(data.mlx, 500, 500);
	if (!data.image.img)
		return (destroy_graphics(&data), free_mlx(&data), free_scene(&sc), 1);
	data.image.addr = mlx_get_data_addr(data.image.img, &data.image.bpp,
			&data.image.line_length, &data.image.endian);
	mlx_loop(data.mlx);
	destroy_graphics(&data);
	free_mlx(&data);
	free_scene(&sc);
	return (0);
}
