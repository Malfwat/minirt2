/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_co_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 19:40:00 by me                #+#    #+#             */
/*   Updated: 2026/11/24 19:40:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Geometrie du cone.
**
** Sommet (0,0,0), axe (0,1,0), base de rayon 1 a la hauteur 3. Le demi-angle
** verifie tan(theta) = rayon / hauteur = 1/3, donc a = cos^2(theta) = 9/10.
** Le rayon de la surface a la hauteur h vaut h/3.
**
**   (0,1,-5) vers +z  -> surface a h=1, rayon 1/3, donc z=-1/3, t=14/3
**   (0,3,-5) vers +z  -> surface a h=3, rayon 1,   donc z=-1,   t=4
**   (2,1,-5) vers +z  -> rate, x=2 depasse le rayon de la surface a h=1
**   (0,-3,-5) vers +z -> rate, c'est la nappe du bas : h negatif
**   (0,5,0)  vers -y  -> bouchon de base a y=3, t=2, normale (0,1,0)
**
** Les valeurs sont calculees a la main, pas mesurees sur le code : c'est le
** contrat. Ce fichier ne compile pas tant que co_hit n'existe pas.
*/

#include "rt_element.h"
#include "rt_math.h"
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

static t_obj	*make_co(double height)
{
	t_obj	*o;

	o = calloc(1, sizeof(t_obj));
	o->id = cone;
	o->coordinate = (t_coordinate){0, 0, 0};
	o->vec = (t_vec3){0, 1, 0};
	o->diameter = 2.0;
	o->height = height;
	o->color = (t_color){200, 100, 50};
	return (o);
}

static int	near(double a, double b)
{
	return (fabs(a - b) < 1e-6);
}

static int	vec_near(t_vec3 a, t_vec3 b)
{
	return (near(a.x, b.x) && near(a.y, b.y) && near(a.z, b.z));
}

static int	hit_at(t_obj *o, t_vec3 from, t_vec3 dir, double t, t_vec3 p)
{
	t_hit	h;

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	if (!co_hit(o, dir, from, &h))
		return (0);
	return (near(h.t, t) && vec_near(h.p, p));
}

static int	misses(t_obj *o, t_vec3 from, t_vec3 dir)
{
	t_hit	h;

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	return (!co_hit(o, dir, from, &h));
}

int	main(void)
{
	t_obj	*o;
	t_obj	*long_co;
	t_hit	h;
	int		ok;

	o = make_co(3.0);
	long_co = make_co(6.0);
	printf("cone : sommet (0,0,0), axe (0,1,0), base r=1 a h=3\n\n");

	ck("fut : h=1, rayon 1/3, t=14/3, point (0,1,-1/3)",
		hit_at(o, (t_vec3){0, 1, -5}, (t_vec3){0, 0, 1}, 14.0 / 3.0,
			(t_vec3){0, 1, -1.0 / 3.0}));
	ck("fut : h=3, rayon 1, t=4, point (0,3,-1)",
		hit_at(o, (t_vec3){0, 3, -5}, (t_vec3){0, 0, 1}, 4.0,
			(t_vec3){0, 3, -1}));

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ok = co_hit(o, (t_vec3){0, 0, 1}, (t_vec3){0, 1, -5}, &h);
	ck("fut : normale unitaire, inclinee hors de l'axe",
		ok && near(get_norme(h.normal), 1.0)
		&& fabs(h.normal.z) > 0.5 && fabs(h.normal.y) > 0.1);

	ck("rate : x=2 depasse le rayon 1/3 de la surface a h=1",
		misses(o, (t_vec3){2, 1, -5}, (t_vec3){0, 0, 1}));
	ck("rate : la nappe du bas est ignoree, h negatif",
		misses(o, (t_vec3){0, -3, -5}, (t_vec3){0, 0, 1}));
	ck("rate : h=4 depasse la hauteur 3",
		misses(o, (t_vec3){0, 4, -5}, (t_vec3){0, 0, 1}));

	ck("bouchon : depuis le dessus, t=2, point (0,3,0)",
		hit_at(o, (t_vec3){0, 5, 0}, (t_vec3){0, -1, 0}, 2.0,
			(t_vec3){0, 3, 0}));
	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ok = co_hit(o, (t_vec3){0, -1, 0}, (t_vec3){0, 5, 0}, &h);
	ck("bouchon : la normale regarde vers le haut", ok && h.normal.y > 0.5);

	ck("bouchon : depuis l'interieur, sortie par la base a t=2",
		hit_at(o, (t_vec3){0, 1, 0}, (t_vec3){0, 1, 0}, 2.0,
			(t_vec3){0, 3, 0}));

	ck("hauteur : le meme rayon touche un cone de hauteur 6, t=13/3",
		hit_at(long_co, (t_vec3){0, 4, -5}, (t_vec3){0, 0, 1},
			13.0 / 3.0, (t_vec3){0, 4, -2.0 / 3.0}));

	free(o);
	free(long_co);
	printf("\n%d cas en echec\n", g_fail);
	return (g_fail != 0);
}
