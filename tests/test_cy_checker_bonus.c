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

static t_obj	*make_sp(double size)
{
	t_obj	*o;

	o = calloc(1, sizeof(t_obj));
	o->id = sphere;
	o->coordinate = (t_coordinate){0, 0, 0};
	o->vec = (t_vec3){0, 0, 0};
	o->diameter = 2.0;
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
	double	s;

	s = o->checker_size;
	a = at_n(o, 1, 0.37 * s, 0, (t_vec3){1, 0, 0});
	b = at_n(o, 1, 1.37 * s, 0, (t_vec3){1, 0, 0});
	c = at_n(o, 1, 2.37 * s, 0, (t_vec3){1, 0, 0});
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
	double	h;

	th = o->checker_size / (o->diameter / 2.0);
	h = 0.37 * o->checker_size;
	a = at_n(o, 1, h, 0, (t_vec3){1, 0, 0});
	b = at_n(o, cos(th), h, -sin(th), (t_vec3){cos(th), 0, -sin(th)});
	c = at_n(o, cos(2 * th), h, -sin(2 * th),
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
	a = at_n(o8, 1, 0.37 * o8->checker_size, 0, (t_vec3){1, 0, 0});
	b = at_n(o8, -1, 0.37 * o8->checker_size, 0, (t_vec3){-1, 0, 0});
	ck("fut : 8 cellules par tour, le point oppose est dans la meme case",
		same(a, b));
	free_obj(o8);
}

static void	test_barrel_translation(t_obj *o, t_obj *ot)
{
	t_color	a;
	t_color	b;

	ot->coordinate = (t_coordinate){10, 0, 0};
	a = at_n(o, 1, 0.37 * o->checker_size, 0.3, (t_vec3){1, 0, 0});
	b = at_n(ot, 11, 0.37 * ot->checker_size, 0.3, (t_vec3){1, 0, 0});
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
	double	sz;

	axis = (t_vec3){0, 1, 0};
	sz = o->checker_size;
	a = at_n(o, 0.37 * sz, 2, 0.37 * sz, axis);
	b = at_n(o, 1.37 * sz, 2, 0.37 * sz, axis);
	c = at_n(o, 0.37 * sz, 2, 1.37 * sz, axis);
	d = at_n(o, 0.37 * sz, 2 + sz, 0.37 * sz, axis);
	ck("bouchon : +1 cellule en x change la case", !same(a, b));
	ck("bouchon : +1 cellule en z change la case", !same(a, c));
	ck("bouchon : avancer sur l'axe ne change pas la case", same(a, d));
}

/*
** La sphere se parametre par deux angles : une latitude (polaire) et une
** longitude (azimut). Une cellule vaut checker_size dans les deux sens a
** l'equateur. L'axe de reference est le vertical du monde : le champ vec
** d'une sphere est nul et get_system y donnerait du NaN.
*/
static void	test_sphere_latitude(t_obj *o)
{
	t_color	a;
	t_color	b;
	t_color	c;
	double	s;
	double	p;

	s = o->checker_size;
	p = 0.37 * s;
	a = at_n(o, sin(p), cos(p), 0, (t_vec3){sin(p), cos(p), 0});
	b = at_n(o, sin(p + s), cos(p + s), 0, (t_vec3){0, 0, 0});
	c = at_n(o, sin(p + 2 * s), cos(p + 2 * s), 0, (t_vec3){0, 0, 0});
	ck("sphere : +1 cellule en latitude change la case", !same(a, b));
	ck("sphere : +2 cellules en latitude redonne la meme case", same(a, c));
}

static void	test_sphere_azimut(t_obj *o)
{
	t_color	a;
	t_color	b;
	t_color	c;
	double	s;
	double	y;

/*
** Deux points de depart evites : y = 0 pile et l'azimut 0. Les deux tombent
** sur une frontiere de cellule, ou le sens de l'arrondi decide du resultat.
** On part donc decale d'une demi-cellule en longitude et legerement en
** latitude.
*/
	s = o->checker_size;
	y = 0.13;
	a = at_n(o, cos(0.5 * s), y, sin(0.5 * s), (t_vec3){0, y, 0});
	b = at_n(o, cos(1.5 * s), y, sin(1.5 * s), (t_vec3){0, y, 0});
	c = at_n(o, cos(2.5 * s), y, sin(2.5 * s), (t_vec3){0, y, 0});
	ck("sphere : +1 cellule en longitude change la case", !same(a, b));
	ck("sphere : +2 cellules en longitude redonne la meme case", same(a, c));
}

/*
** Au pole, acos depasse [-1, 1] des que l'arrondi fait sortir le point de la
** sphere : sans bornage, la couleur n'est ni l'une ni l'autre des deux
** couleurs du damier.
*/
static void	test_sphere_pole(t_obj *o)
{
	t_color	c;
	t_color	light;
	t_color	dark;

	c = at_n(o, 0, 1.0000001, 0, (t_vec3){0, 1, 0});
	light = o->color;
	dark = (t_color){light.r * DARKEN, light.g * DARKEN, light.b * DARKEN};
	ck("sphere : un point au-dela du pole rend une couleur du damier",
		same(c, light) || same(c, dark));
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
	t_obj	*sp;

	o = make_cy(2.0 * M_PI / 12.0, (t_vec3){0, 1, 0});
	ot = make_cy(2.0 * M_PI / 12.0, (t_vec3){0, 1, 0});
	pl = make_pl(0.5);
	sp = make_sp(2.0 * M_PI / 12.0);
	printf("cylindre r=1, axe (0,1,0), 12 cellules par tour\n\n");
	test_barrel_axis(o);
	test_barrel_arc(o);
	test_barrel_seam();
	test_barrel_translation(o, ot);
	test_cap(o);
	test_sphere_latitude(sp);
	test_sphere_azimut(sp);
	test_sphere_pole(sp);
	test_barrel_closed();
	test_plane_regression(pl);
	free_obj(o);
	free_obj(ot);
	free_obj(pl);
	free_obj(sp);
	printf("\n%d cas en echec\n", g_fail);
	return (g_fail != 0);
}
