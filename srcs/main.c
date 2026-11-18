/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/11/18 18:48:35 by me               ###   ########.fr       */
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

bool	init_graphics(t_graphics *data)
{
	ft_bzero(data, sizeof(t_graphics));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (false);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello World!");
	if (!data->win)
		return (false);
	mlx_key_hook(data->win, keyhook, data);
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image.img)
		return (false);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.line_length, &data->image.endian);
	mlx_hook(data->win, W_CROSS, 0, stop_loop, data);
	return (true);
}

int	main(int ac, char **av)
{
	t_graphics	data;
	t_scene		sc;
	t_err		err;

	ft_bzero(&sc, sizeof(t_scene));
	if (ac != 2 || NB_TH < 0)
		return (0);
	parse(av[1], &sc);
	if (!init_graphics(&data))
		return (free_scene(&sc), destroy_graphics(&data), 1);
	err = render(&data, &sc);
	if (err != ok)
	{
		destroy_graphics(&data);
		manage_error_and_exit(err, &sc, NOT_A_LINE);
	}
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_loop(data.mlx);
	destroy_graphics(&data);
	free_scene(&sc);
	return (0);
}
