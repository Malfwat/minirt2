/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 00:11:55 by me                #+#    #+#             */
/*   Updated: 2026/11/21 03:59:42 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"
#include "rt_graphics.h"
#include "rt_graphics_bonus.h"

#include "mlx.h"

#include <sys/time.h>

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
	mlx_hook(data->win, W_CROSS, 0, stop_loop, param);
	return (true);
}

void	exit_prog(t_render *param)
{
	close_sem_tab(param->sem_printing, NB_TH);
	close_sem_tab(param->sem_stop, NB_TH);
	destroy_graphics(&param->data);
	if (param->err != ok)
		manage_error_and_exit(syscall_err, &param->sc, NOT_A_LINE);
	free_scene(&param->sc);
}

int	main(int ac, char **av)
{
	t_render	param;

	ft_bzero(&param, sizeof(param));
	if (ac != 2 || NB_TH < 0)
		return (1); // ajouter un usage
	parse(av[1], &param.sc);
	if (!init_graphics(&param.data, &param))
		return (free_scene(&param.sc), destroy_graphics(&param.data), 1);
	if (!init_sem_tab(param.sem_stop))
	{
		destroy_graphics(&param.data);
		manage_error_and_exit(syscall_err, &param.sc, NOT_A_LINE);
	}
	if (!init_sem_tab(param.sem_printing)
		|| gettimeofday(&param.last, NULL))
	{
		close_sem_tab(param.sem_stop, NB_TH);
		destroy_graphics(&param.data);
		manage_error_and_exit(syscall_err, &param.sc, NOT_A_LINE);
	}
	build_frame(&param.data, &param.sc);
	mlx_loop_hook(param.data.mlx, rendering_loop, &param);
	mlx_loop(param.data.mlx);
	return (exit_prog(&param), 0);
}
