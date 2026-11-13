/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/11/13 14:52:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_struct.h"
#include "rt.h"
#include "str.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	t_scene	sc;

	ft_bzero(&sc, sizeof(t_scene));
	if (ac != 2)
		return (0);
	parse(av[1], &sc);
	printf("%i, %f\n", sc.amb.color.b, sc.amb.ratio);
	printf("%i, %f\n", sc.light_lst->color.b, sc.light_lst->coordinate.x);
	free_scene(&sc);
	return (0);
}
