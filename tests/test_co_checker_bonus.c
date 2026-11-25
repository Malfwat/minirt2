/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_co_checker_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 01:05:00 by me                #+#    #+#             */
/*   Updated: 2026/11/25 01:05:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Damier du cone.
**
** Sommet (0,0,0), axe (0,1,0), diametre 2 donc base de rayon 1 a la hauteur 3,
** damier 0,5. Alors tour = 2PI, n = 12 colonnes, et cell = 0,5236 sur la surface.
**
** Les points sont construits sur la surface : a la hauteur h le rayon vaut h/3,
** et la distance au sommet vaut h * sqrt(1 + 1/9) = h * 1,05409.
** Un pas de v vaut donc 0,5236 / 1,05409 = 0,49673 de hauteur.
**
** Toutes les assertions portent sur des DIFFERENCES entre deux points, jamais
** sur une parite absolue : le repere tangent du moteur peut etre tourne autour
** de l'axe par rapport a celui du test, ce qui decale u d'une constante.
**
** Le cas 45 degres est le regression test : avec un azimut mesure dans le plan
** xz du monde, une colonne y valait deux, et ces assertions tombaient.
*/

#include "rt_config.h"
#include "rt_element.h"
#include "rt_math.h"
#include "rt_render.h"
#include "rt_struct.h"

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

static t_obj	*make_co(t_vec3 axis, double height, double diameter, double size)
{
	t_obj	*o;

	o = calloc(1, sizeof(t_obj));
	o->id = cone;
	o->coordinate = (t_coordinate){0, 0, 0};
	o->vec = normalize(axis);
	o->height = height;
	o->diameter = diameter;
	o->color = (t_color){200, 100, 50};
	o->checker_size = size;
	return (o);
}

static void	frame(t_vec3 axis, t_vec3 *t1, t_vec3 *t2)
{
	t_vec3	helper;

	helper = (t_vec3){0, 0, 1};
	if (fabs(scal(axis, helper)) > 0.9)
		helper = (t_vec3){1, 0, 0};
	*t1 = normalize(cross(axis, helper));
	*t2 = normalize(cross(axis, *t1));
}

/* Point de la surface : hauteur h au-dessus du sommet, azimut a. */
static t_hit	side_point(t_obj *o, double h, double a)
{
	t_hit	hit;
	t_vec3	t1;
	t_vec3	t2;
	double	radius;

	frame(o->vec, &t1, &t2);
	radius = h * (o->diameter / 2) / o->height;
	hit.p = add(add(o->coordinate, mult(o->vec, h)),
			add(mult(t1, radius * cos(a)), mult(t2, radius * sin(a))));
	hit.normal = normalize(sub(sub(hit.p, o->coordinate),
				mult(o->vec, h)));
	hit.t = h;
	return (hit);
}

static int	same(t_color a, t_color b)
{
	return (fabs(a.r - b.r) < 1e-9 && fabs(a.g - b.g) < 1e-9
		&& fabs(a.b - b.b) < 1e-9);
}

/* Pas angulaire d'une colonne, puis deux colonnes. */
static void	azimut_test(t_obj *o, const char *label, double h)
{
	double	n;
	double	step;
	t_color	c0;
	t_color	c1;
	t_color	c2;

	n = 2 * round(M_PI * o->diameter / (2 * o->checker_size));
	step = 2 * M_PI / n;
	c0 = co_checker(side_point(o, h, 0.7 * step), o);
	c1 = co_checker(side_point(o, h, 1.7 * step), o);
	c2 = co_checker(side_point(o, h, 2.7 * step), o);
	ck(label, !same(c0, c1) && same(c0, c2));
	(void)label;
}

int	main(void)
{
	t_obj	*o;
	t_obj	*tilt;
	t_hit	h1;
	t_hit	h2;
	t_hit	cap;
	t_hit	cap_inv;
	double	cell;
	double	dh;
	t_color	light;
	t_color	dark;

	o = make_co((t_vec3){0, 1, 0}, 3.0, 2.0, 0.5);
	tilt = make_co((t_vec3){0.72, -0.69, 0}, 3.0, 2.0, 0.5);
	cell = M_PI * o->diameter / 12.0;
	dh = cell / (sqrt(1.0 + 1.0 / 9.0));
	light = o->color;
	dark = (t_color){light.r * DARKEN, light.g * DARKEN, light.b * DARKEN};

	printf("cone : sommet (0,0,0), base r=1 a h=3, damier 0.5 -> 12 colonnes\n");
	printf("cellule %.4f sur la surface, soit %.4f de hauteur\n\n", cell, dh);

	azimut_test(o, "fut vertical : 1 colonne change, 2 colonnes identiques", 2.4);
	azimut_test(tilt, "fut incline 45 deg : idem", 2.4);
	azimut_test(o, "le pas angulaire ne depend pas de la hauteur", 0.6);

	h1 = side_point(o, 1.0, 0.7);
	h2 = side_point(o, 1.0 + dh, 0.7);
	ck("pente : une cellule de plus change la case",
		!same(co_checker(h1, o), co_checker(h2, o)));
	h2 = side_point(o, 1.0 + 2 * dh, 0.7);
	ck("pente : deux cellules de plus redonne la meme case",
		same(co_checker(h1, o), co_checker(h2, o)));

	memset(&cap, 0, sizeof(cap));
	cap.p = (t_vec3){0.3, 3.0, 0.2};
	cap.normal = o->vec;
	memset(&cap_inv, 0, sizeof(cap_inv));
	cap_inv.p = cap.p;
	cap_inv.normal = mult(o->vec, -1.0);
	ck("bouchon : meme couleur que disk_checker",
		same(co_checker(cap, o), disk_checker(cap, o)));
	ck("bouchon : la normale retournee ne change pas la case",
		same(co_checker(cap, o), co_checker(cap_inv, o)));

	h1 = side_point(o, 0.05, 0.3);
	ck("sommet : un point tres proche ne produit pas de bruit",
		same(co_checker(h1, o), light) || same(co_checker(h1, o), dark));

	h1 = side_point(o, 2.4, 0.7);
	ck("fut : les deux couleurs sont bien la couleur et sa version sombre",
		(same(co_checker(h1, o), light) || same(co_checker(h1, o), dark)));

	free(o);
	free(tilt);
	printf("\n%d cas en echec\n", g_fail);
	return (g_fail != 0);
}
