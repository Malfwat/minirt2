/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:11:55 by me                #+#    #+#             */
/*   Updated: 2026/11/21 02:14:52 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"
#include "rt_graphics.h"
#include "rt_graphics_bonus.h"

#include "mlx.h"

static bool	init_graphics(t_graphics *data, t_render *param)
{
	ft_bzero(data, sizeof(t_graphics));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (false);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!data->win)
		return (false);
	mlx_key_hook(data->win, keyhook, param);
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
	t_render	param;

	param.stop = false;
	ft_bzero(&param.sc, sizeof(t_scene));
	if (ac != 2 || NB_TH < 0)
		return (0); // ajouter un usage
	parse(av[1], &param.sc);
	if (!init_graphics(&param.data, &param))
		return (free_scene(&param.sc), destroy_graphics(&param.data), 1);
	if (sem_init(&param.sem_stop, 0, 1))
	{
		destroy_graphics(&param.data);
		manage_error_and_exit(syscall_err, &param.sc, NOT_A_LINE);
	}
	if (sem_init(&param.sem_printing, 0, NB_TH))
	{
		sem_destroy(&param.sem_stop);
		destroy_graphics(&param.data);
		manage_error_and_exit(syscall_err, &param.sc, NOT_A_LINE);
	}
	build_frame(&param.data, &param.sc);
	mlx_loop_hook(param.data.mlx, rendering_loop, &param);
	mlx_loop(param.data.mlx);
	if (param.err != ok)
	{
		sem_destroy(&param.sem_stop);
		destroy_graphics(&param.data);
		manage_error_and_exit(syscall_err, &param.sc, NOT_A_LINE);
	}
	sem_destroy(&param.sem_stop);
	destroy_graphics(&param.data);
	free_scene(&param.sc);
	return (0);
}
