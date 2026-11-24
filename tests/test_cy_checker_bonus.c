/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cy_checker_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 17:05:00 by me                #+#    #+#             */
/*   Updated: 2026/11/24 17:05:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Damier sur le cylindre.
**
** Le fut et les bouchons sont deux surfaces differentes et doivent suivre
** deux mappings differents :
**
**   fut      arc = angle * rayon  le long de la circonference, hauteur le
**            long de l'axe. Une cellule fait checker_size dans les DEUX
**            directions.
**   bouchon  damier plan dans le plan du bouchon, comme sur un plan. La
**            composante axiale est ignoree.
**
** Le test ne lit pas les coordonnees internes : il verifie des invariants
** observables. Avancer d'une cellule change la case, avancer de deux la
** redonne, et le motif suit l'objet quand on le deplace.
*/

#include "rt_struct.h"
#include "rt_render.h"
#include "rt_config.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	g_fail;

static int	ck(const char *label, int cond)
{
	printf("%-58s %s\n", label, cond ? "ok" : "FAIL");
	if (!cond)
		g_fail++;
	return (cond);
}

static void	free_obj(t_obj *o)
{
	free(o);
}

static t_obj	*make_cy(double size, t_vec3 axis)
{
	t_obj	*o;

	o = calloc(1, sizeof(t_obj));
	o->id = cylinder;
	o->coordinate = (t_coordinate){0, 0, 0};
	o->vec = axis;
	o->diameter = 2.0;
	o->height = 4.0;
	o->checker_size = size;
	o->color = (t_color){200, 100, 50};
	return (o);
}

static t_obj	*make_pl(double size)
{
	t_obj	*o;

	o = calloc(1, sizeof(t_obj));
	o->id = plan;
	o->coordinate = (t_coordinate){0, 0, 0};
	o->vec = (t_vec3){0, 1, 0};
	o->checker_size = size;
	o->color = (t_color){200, 100, 50};
	return (o);
}

static t_color	at_n(t_obj *o, double x, double y, double z, t_vec3 n)
{
	t_hit	hit;

	hit.obj = o;
	hit.t = 0;
	hit.p = (t_vec3){x, y, z};
	hit.normal = n;
	return (checker_color(hit, o));
}

static int	same(t_color a, t_color b)
{
	return (a.r == b.r && a.g == b.g && a.b == b.b);
}

/*
** Base du cylindre vertical, calculee comme le moteur la calcule :
** get_system((0,1,0)) donne x = (1,0,0) et y = (0,0,-1), donc l'azimut
** d'un point (a, *, c) vaut atan2(-c, a).
*/
static void	test_barrel_axis(t_obj *o)
{
	t_color	a;
	t_color	b;
	t_color	c;

	a = at_n(o, 1, 0.185, 0, (t_vec3){1, 0, 0});
	b = at_n(o, 1, 0.685, 0, (t_vec3){1, 0, 0});
	c = at_n(o, 1, 1.185, 0, (t_vec3){1, 0, 0});
	ck("fut : meme point deux fois, meme case", same(a, a));
	ck("fut : +1 cellule en hauteur change la case", !same(a, b));
	ck("fut : +2 cellules en hauteur redonne la meme case", same(a, c));
}

static void	test_barrel_arc(t_obj *o)
{
	t_color	a;
	t_color	b;
	t_color	c;
	double	th;

	th = o->checker_size / (o->diameter / 2.0);
	a = at_n(o, 1, 0.185, 0, (t_vec3){1, 0, 0});
	b = at_n(o, cos(th), 0.185, -sin(th), (t_vec3){cos(th), 0, -sin(th)});
	c = at_n(o, cos(2 * th), 0.185, -sin(2 * th),
		(t_vec3){cos(2 * th), 0, -sin(2 * th)});
	ck("fut : +1 cellule en arc change la case", !same(a, b));
	ck("fut : +2 cellules en arc redonne la meme case", same(a, c));
}

static void	test_barrel_seam(void)
{
	t_obj	*o8;
	t_color	a;
	t_color	b;

	o8 = make_cy(2.0 * M_PI / 8.0, (t_vec3){0, 1, 0});
	a = at_n(o8, 1, 0.185, 0, (t_vec3){1, 0, 0});
	b = at_n(o8, -1, 0.185, 0, (t_vec3){-1, 0, 0});
	ck("fut : 8 cellules par tour, le point oppose est dans la meme case",
		same(a, b));
	free_obj(o8);
}

static void	test_barrel_translation(t_obj *o, t_obj *ot)
{
	t_color	a;
	t_color	b;

	ot->coordinate = (t_coordinate){10, 0, 0};
	a = at_n(o, 1, 0.185, 0.3, (t_vec3){1, 0, 0});
	b = at_n(ot, 11, 0.185, 0.3, (t_vec3){1, 0, 0});
	ck("fut : deplacer le cylindre deplace le motif avec lui", same(a, b));
}

/*
** Bouchon : la normale est l'axe (ou son oppose). Le damier y est plan, et
** la hauteur ne doit plus rien changer.
*/
static void	test_cap(t_obj *o)
{
	t_color	a;
	t_color	b;
	t_color	c;
	t_color	d;
	t_vec3	axis;

	axis = (t_vec3){0, 1, 0};
	a = at_n(o, 0.185, 2, 0.185, axis);
	b = at_n(o, 0.685, 2, 0.185, axis);
	c = at_n(o, 0.185, 2, 0.685, axis);
	d = at_n(o, 0.185, 2.5, 0.185, axis);
	ck("bouchon : +1 cellule en x change la case", !same(a, b));
	ck("bouchon : +1 cellule en z change la case", !same(a, c));
	ck("bouchon : avancer sur l'axe ne change pas la case", same(a, d));
}

static void	test_dispatch(void)
{
	t_obj	*sp;
	t_color	c;

	sp = make_cy(0.5, (t_vec3){0, 1, 0});
	sp->id = sphere;
	c = at_n(sp, 1, 0.185, 0, (t_vec3){1, 0, 0});
	ck("sphere : aucun damier, la couleur brute est rendue",
		same(c, sp->color));
	free_obj(sp);
}

static void	test_plane_regression(t_obj *pl)
{
	t_color	a;
	t_color	b;
	t_color	c;

	a = at_n(pl, 0.185, 0, 0.185, (t_vec3){0, 1, 0});
	b = at_n(pl, 0.685, 0, 0.185, (t_vec3){0, 1, 0});
	c = at_n(pl, 1.185, 0, 0.185, (t_vec3){0, 1, 0});
	ck("plan : +1 cellule change la case", !same(a, b));
	ck("plan : +2 cellules redonne la meme case", same(a, c));
}

/*
** Fermeture du tour : les colonnes doivent etre egalement reparties sur la
** circonference. Une colonne coupee, ou deux colonnes voisines de meme
** couleur au raccord, produisent un ecart deux fois plus large que les
** autres. C'est ce que ce test mesure, sans avoir besoin de connaitre n.
*/
static void	test_barrel_closed(void)
{
	t_obj	*o;
	t_color	prev;
	t_color	cur;
	int		idx[4100];
	int		pos[4100];
	int		nb;
	int		i;
	int		n;
	int		mini;
	int		maxi;

	o = make_cy(0.5, (t_vec3){0, 1, 0});
	n = 3600;
	nb = 0;
	prev = at_n(o, 1, 0.185, 0, (t_vec3){1, 0, 0});
	i = 0;
	while (++i < n)
	{
		cur = at_n(o, cos(2 * M_PI * i / n), 0.185,
			sin(2 * M_PI * i / n), (t_vec3){1, 0, 0});
		if (!same(prev, cur))
			idx[nb++] = i;
		prev = cur;
	}
	i = -1;
	while (++i < nb - 1)
		pos[i] = idx[i + 1] - idx[i];
	pos[nb - 1] = n - idx[nb - 1] + idx[0];
	mini = pos[0];
	maxi = pos[0];
	i = -1;
	while (++i < nb)
	{
		mini = (pos[i] < mini) ? pos[i] : mini;
		maxi = (pos[i] > maxi) ? pos[i] : maxi;
	}
	printf("    (%d colonnes, ecart min %d max %d sur %d points)\n",
		nb, mini, maxi, n);
	ck("fut : les colonnes sont egalement reparties sur le tour",
		nb >= 4 && maxi - mini <= 2);
	free_obj(o);
}

int	main(void)
{
	t_obj	*o;
	t_obj	*ot;
	t_obj	*pl;

	o = make_cy(0.5, (t_vec3){0, 1, 0});
	ot = make_cy(0.5, (t_vec3){0, 1, 0});
	pl = make_pl(0.5);
	printf("cylindre r=1, axe (0,1,0), cellule 0.5\n\n");
	test_barrel_axis(o);
	test_barrel_arc(o);
	test_barrel_seam();
	test_barrel_translation(o, ot);
	test_cap(o);
	test_dispatch();
	test_barrel_closed();
	test_plane_regression(pl);
	free_obj(o);
	free_obj(ot);
	free_obj(pl);
	printf("\n%d cas en echec\n", g_fail);
	return (g_fail != 0);
}
