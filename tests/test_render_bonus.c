/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 20:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/18 20:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_struct.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>

static int	g_fail;
static int	g_total;

static void	check(int cond, const char *what)
{
	g_total++;
	if (!cond)
	{
		g_fail++;
		printf("FAIL  %s\n", what);
	}
}

static unsigned char	*px(char *buf, t_graphics *g, int x, int y)
{
	return ((unsigned char *)(buf + y * g->image.line_length
			+ x * (g->image.bpp / 8)));
}

static int	black_pixels(char *buf, t_graphics *g)
{
	int	x;
	int	y;
	int	n;

	n = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (px(buf, g, x, y)[0] == 0 && px(buf, g, x, y)[1] == 0
				&& px(buf, g, x, y)[2] == 0)
				n++;
			x++;
		}
		y++;
	}
	return (n);
}

static int	max_row_jump(char *buf, t_graphics *g)
{
	int	x;
	int	y;
	int	d;
	int	max;

	max = 0;
	y = 1;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			d = px(buf, g, x, y)[1] - px(buf, g, x, y - 1)[1];
			if (d < 0)
				d = -d;
			if (d > max)
				max = d;
			x++;
		}
		y++;
	}
	return (max);
}

int	main(void)
{
	char		*buf;
	t_graphics	g;
	t_scene		sc;
	t_err		err;

	buf = calloc(WIDTH * HEIGHT, 4);
	check(buf != NULL, "allocation du faux buffer");
	ft_bzero(&g, sizeof(g));
	ft_bzero(&sc, sizeof(sc));
	sc.cam.fov = 70;
	sc.cam.vec.z = 1;
	g.image.addr = buf;
	g.image.bpp = 32;
	g.image.line_length = WIDTH * 4;
	err = render(&g, &sc);
	check(err == ok, "render bonus renvoie ok");
	check(black_pixels(buf, &g) == 0, "tous les pixels sont ecrits (aucun noir)");
	check(max_row_jump(buf, &g) <= 3, "aucune couture entre les bandes");
	free(buf);
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
