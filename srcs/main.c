/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/11/14 11:27:27 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"

#include "mlx.h"
#include "mlx_int.h"

void	free_mlx(t_xvar *xvar)
{
	mlx_destroy_display(xvar);
	free(xvar);
}

void	destroy_graphics(t_xvar *xvar)
{
	mlx_destroy_window(xvar, xvar->win_list);
}

int	main(int ac, char **av)
{
	t_xvar	*xvar;
	t_scene	sc;

	ft_bzero(&sc, sizeof(t_scene));
	if (ac != 2)
		return (0);
	parse(av[1], &sc);
	xvar = mlx_init();
	if (!xvar)
		return (free_scene(&sc), 1);
	if (!mlx_new_window(xvar, 500, 500, "Hello World!"))
		return (free_scene(&sc), 1);
	sleep(5);
	destroy_graphics(xvar);
	free_mlx(xvar);
	free_scene(&sc);
	return (0);
}
