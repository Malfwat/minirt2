/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/11/22 20:30:20 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"
#include "rt_graphics.h"

#include "mlx.h"

static bool	init_graphics(t_graphics *data)
{
	ft_bzero(data, sizeof(t_graphics));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (false);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!data->win)
		return (false);
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
	t_rt	rt;

	ft_bzero(&rt, sizeof(rt));
	if (ac != 2)
		return (ft_putstr_fd(USAGE, 2), 1);
	parse(av[1], &rt.sc);
	if (!init_graphics(&rt.data))
		return (free_scene(&rt.sc), destroy_graphics(&rt.data), 1);
	mlx_key_hook(rt.data.win, keyhook, &rt);
	mlx_loop_hook(rt.data.mlx, rendering_loop, &rt);
	mlx_loop(rt.data.mlx);
	destroy_graphics(&rt.data);
	free_scene(&rt.sc);
	return (0);
}
