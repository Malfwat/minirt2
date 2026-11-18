/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_render.c */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics.h"
#include "rt_struct.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int	max_jump(char *buf, t_graphics *g)
{
	int	x;
	int	y;
	int	c;
	int	d;
	int	max;

	max = 0;
	y = 1;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = 0;
			while (c < 3)
			{
				d = px(buf, g, x, y)[c] - px(buf, g, x, y - 1)[c];
				if (d < 0)
					d = -d;
				if (d > max)
					max = d;
				c++;
			}
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
	unsigned char	*p;

	buf = calloc(WIDTH * HEIGHT, 4);
	check(buf != NULL, "allocation du faux buffer");
	sc.cam.fov = 70;
	ft_bzero(&g, sizeof(g));
	g.image.addr = buf;
	g.image.bpp = 32;
	g.image.line_length = WIDTH * 4;
	/* frame fov 70 : tan(35) et tan(35) * 600 / 900 */
	g.ox = 0.7002075382;
	g.oy = 0.4668050255;
	/* frame d'une camera qui regarde vers +z : x=-X, y=+Y, z=+Z */
	g.axes.x.x = -1; g.axes.y.y = 1; g.axes.z.z = 1;
	put_pxl(0, 0, &g, 0x00112233);
	p = px(buf, &g, 0, 0);
	check(p[0] == 0x33 && p[1] == 0x22 && p[2] == 0x11, "ordre BGR little-endian");
	put_pxl(10, 3, &g, 0x00ff0000);
	p = px(buf, &g, 10, 3);
	check(p[0] == 0 && p[1] == 0 && p[2] == 0xff, "pixel 10,3 = rouge pur");
	check(px(buf, &g, 11, 3)[0] == 0, "pas de debordement a droite");
	put_pxl(WIDTH - 1, HEIGHT - 1, &g, 0x000000ff);
	p = px(buf, &g, WIDTH - 1, HEIGHT - 1);
	check(p[0] == 0xff, "dernier pixel de l'image");
	ft_bzero(buf, WIDTH * HEIGHT * 4);
	render_lines(0, 10, &g, &sc);
	check(px(buf, &g, WIDTH - 1, 9)[0] != 0, "render_lines ecrit la ligne 9");
	check(px(buf, &g, WIDTH - 1, 0)[0] != 0, "render_lines ecrit la ligne 0 en x max");
	check(px(buf, &g, 0, 10)[0] == 0 && px(buf, &g, 0, 10)[1] == 0
		&& px(buf, &g, 0, 10)[2] == 0, "borne haute exclue: ligne 10 intacte");
	ft_bzero(buf, WIDTH * HEIGHT * 4);
	render_lines(HEIGHT - 1, HEIGHT, &g, &sc);
	check(px(buf, &g, WIDTH - 1, HEIGHT - 1)[0] != 0, "derniere bande d'une ligne");
	ft_bzero(buf, WIDTH * HEIGHT * 4);
	render_lines(HEIGHT / 2, HEIGHT / 2 + 1, &g, &sc);
	ft_bzero(buf, WIDTH * HEIGHT * 4);
	render_lines(0, HEIGHT, &g, &sc);
	p = px(buf, &g, WIDTH / 2, HEIGHT / 2);
	check(p[2] == 127 && p[1] == 127 && p[0] >= 250,
		"pixel central = axes.z encode (0,0,1) -> 127,127,254");
	check(px(buf, &g, 0, HEIGHT / 2)[2] > px(buf, &g, WIDTH - 1, HEIGHT / 2)[2],
		"l'axe x de l'ecran vaut -X du monde : rouge decroissant");
	check(px(buf, &g, WIDTH / 2, 0)[1] > px(buf, &g, WIDTH / 2, HEIGHT - 1)[1],
		"le vert croit vers le haut");
	g.axes.x.x = 0.8; g.axes.x.y = -0.6; g.axes.x.z = 0;
	g.axes.y.x = 0; g.axes.y.y = 0; g.axes.y.z = -1;
	g.axes.z.x = 0.6; g.axes.z.y = 0.8; g.axes.z.z = 0;
	ft_bzero(buf, WIDTH * HEIGHT * 4);
	render_lines(HEIGHT / 2, HEIGHT / 2 + 1, &g, &sc);
	p = px(buf, &g, WIDTH / 2, HEIGHT / 2);
	check(p[2] == 204 && p[1] == 229 && p[0] == 127,
		"camera inclinee : le centre encode le nouveau axes.z (204,229,127)");

	/* camera tres inclinee + grand fov : vec.z change de signe dans l'image.
	   Aucun canal ne doit reboucler (ancien bug : b = vec.z * 255). */
	g.axes.x.x = -0.9180; g.axes.x.y = 0.0; g.axes.x.z = 0.3967;
	g.axes.y.x = -0.1834; g.axes.y.y = 0.8868; g.axes.y.z = -0.4244;
	g.axes.z.x = 0.3517; g.axes.z.y = 0.4623; g.axes.z.z = 0.8140;
	g.ox = 5.6713;
	g.oy = 5.6713 * (double)HEIGHT / (double)WIDTH;
	ft_bzero(buf, (size_t)WIDTH * HEIGHT * 4);
	render_lines(0, HEIGHT, &g, &sc);
	check(max_jump(buf, &g) <= 2, "aucun canal ne reboucle quand vec.z change de signe");
	free(buf);
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
