/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cy_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 19:30:00 by me                #+#    #+#             */
/*   Updated: 2026/11/24 19:30:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Geometrie du cylindre ferme : cy_hit renvoie le point d'impact le plus
** proche sur le fut ou sur l'un des deux bouchons, avec sa normale.
**
** Objet de reference : centre (0,0,0), axe (0,1,0), diametre 2 donc rayon 1,
** hauteur 4 donc le fut va de y = -2 a y = +2.
**
**   (0,0,-5) vers +z   -> fut a t=4, normale (0,0,-1)
**   (0,5,0)  vers -y   -> bouchon haut a t=3, normale (0,1,0)
**   (2,0,-5) vers +z   -> rate, x depasse le rayon
**   (0,5,-1) vers +z   -> rate, y depasse le haut : le fut est borne
*/

#include "rt_element.h"
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

static t_obj	*make_cy(double height)
{
	t_obj	*o;

	o = calloc(1, sizeof(t_obj));
	o->id = cylinder;
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

static int	hit_at(t_obj *o, t_vec3 from, t_vec3 dir, double t, t_vec3 p,
	t_vec3 n)
{
	t_hit	h;

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	if (!cy_hit(o, dir, from, &h))
		return (0);
	return (near(h.t, t) && vec_near(h.p, p) && vec_near(h.normal, n));
}

int	main(void)
{
	t_obj	*o;
	t_obj	*tall;
	t_hit	h;

	o = make_cy(4.0);
	tall = make_cy(10.0);
	printf("cylindre : centre (0,0,0), axe (0,1,0), rayon 1, hauteur 4\n\n");

	ck("fut : face avant, t=4, normale (0,0,-1)",
		hit_at(o, (t_vec3){0, 0, -5}, (t_vec3){0, 0, 1}, 4.0,
			(t_vec3){0, 0, -1}, (t_vec3){0, 0, -1}));
	ck("fut : face arriere vue de derriere, normale (0,0,1)",
		hit_at(o, (t_vec3){0, 0, 5}, (t_vec3){0, 0, -1}, 4.0,
			(t_vec3){0, 0, 1}, (t_vec3){0, 0, 1}));
	ck("fut : depuis l'interieur, sortie a t=1, normale (0,0,1)",
		hit_at(o, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 1}, 1.0,
			(t_vec3){0, 0, 1}, (t_vec3){0, 0, 1}));

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("bouchon : dessus, t=3, normale (0,1,0)",
		cy_hit(o, (t_vec3){0, -1, 0}, (t_vec3){0, 5, 0}, &h)
		&& near(h.t, 3.0) && vec_near(h.p, (t_vec3){0, 2, 0})
		&& vec_near(h.normal, (t_vec3){0, 1, 0}));
	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("bouchon : dessous, t=3, normale (0,-1,0)",
		cy_hit(o, (t_vec3){0, 1, 0}, (t_vec3){0, -5, 0}, &h)
		&& near(h.t, 3.0) && vec_near(h.p, (t_vec3){0, -2, 0})
		&& vec_near(h.normal, (t_vec3){0, -1, 0}));
	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("bouchon : pres du bord, toujours touche",
		cy_hit(o, (t_vec3){0, -1, 0}, (t_vec3){0.99, 5, 0}, &h)
		&& near(h.t, 3.0) && vec_near(h.p, (t_vec3){0.99, 2, 0}));

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("rate : x=2 depasse le rayon et la rayon est parallele aux bouchons",
		!cy_hit(o, (t_vec3){0, 0, 1}, (t_vec3){2, 0, -5}, &h));
	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("rate : y=3 au-dessus du bouchon, rayon parallele a l'axe",
		!cy_hit(o, (t_vec3){0, 0, 1}, (t_vec3){0, 3, -1}, &h));
	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("rate : rayon hors du champ, (5,5,-5) vers +z",
		!cy_hit(o, (t_vec3){0, 0, 1}, (t_vec3){5, 5, -5}, &h));

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("hauteur bornee : y=4 ne touche pas le cylindre de hauteur 4",
		!cy_hit(o, (t_vec3){0, 0, 1}, (t_vec3){0, 4, -5}, &h));
	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("hauteur bornee : le meme rayon touche celui de hauteur 10",
		cy_hit(tall, (t_vec3){0, 0, 1}, (t_vec3){0, 4, -5}, &h)
		&& near(h.t, 4.0) && vec_near(h.p, (t_vec3){0, 4, -1})
		&& vec_near(h.normal, (t_vec3){0, 0, -1}));

	memset(&h, 0, sizeof(h));
	h.t = INFINITY;
	ck("rase : le rayon tangent donne une racine double ou rien",
		(!cy_hit(o, (t_vec3){0, 0, 1}, (t_vec3){1, 0, -5}, &h)
			|| near(h.t, 5.0)));

	free(o);
	free(tall);
	printf("\n%d cas en echec\n", g_fail);
	return (g_fail != 0);
}
