/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/11/14 12:16:15 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"

#include "mlx.h"

#include <stdlib.h>
#include <unistd.h> // sleep

void	free_mlx(t_graphics *data)
{
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	destroy_graphics(t_graphics *data)
{
	mlx_destroy_window(data->mlx, data->win);
}

int	main(int ac, char **av)
{
	t_graphics	data;
	t_scene		sc;

	ft_bzero(&sc, sizeof(t_scene));
	if (ac != 2)
		return (0);
	parse(av[1], &sc);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free_scene(&sc), 1);
	data.win = mlx_new_window(data.mlx, 500, 500, "Hello World!");
	if (!data.win)
		return (free_mlx(data.mlx), free_scene(&sc), 1);
	sleep(1);
	destroy_graphics(&data);
	free_mlx(&data);
	free_scene(&sc);
	return (0);
}
