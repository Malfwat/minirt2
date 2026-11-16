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

int	main(void)
{
	char		*buf;
	t_graphics	g;
	unsigned char	*p;

	buf = calloc(WIDTH * HEIGHT, 4);
	check(buf != NULL, "allocation du faux buffer");
	ft_bzero(&g, sizeof(g));
	g.image.addr = buf;
	g.image.bpp = 32;
	g.image.line_length = WIDTH * 4;
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
	render_lines(0, 10, &g, NULL);
	check(px(buf, &g, WIDTH - 1, 9)[2] != 0, "render_lines ecrit la ligne 9");
	check(px(buf, &g, WIDTH - 1, 0)[2] != 0, "render_lines ecrit la ligne 0 en x max");
	check(px(buf, &g, 0, 10)[0] == 0 && px(buf, &g, 0, 10)[1] == 0
		&& px(buf, &g, 0, 10)[2] == 0, "borne haute exclue: ligne 10 intacte");
	ft_bzero(buf, WIDTH * HEIGHT * 4);
	render_lines(HEIGHT - 1, HEIGHT, &g, NULL);
	check(px(buf, &g, WIDTH - 1, HEIGHT - 1)[2] != 0, "derniere bande d'une ligne");
	free(buf);
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
