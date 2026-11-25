/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_co_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 19:35:00 by me                #+#    #+#             */
/*   Updated: 2026/11/24 19:35:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Parsing de la ligne cone.
**
**   "x,y,z  vx,vy,vz  diametre_base  hauteur  r,g,b"              5 champs
**   plus [intensite exposant]                                   7 champs
**   plus [taille_damier]                                        8 champs
**
** Le point de la ligne est le SOMMET du cone, l'axe va du sommet vers la base.
** Le diametre est celui de la base. Rien entre ces trois longueurs : six
** champs, quatre champs et neuf champs sont refuses.
**
** Ce fichier ne compile pas tant que l'enumeration n'a pas de valeur `cone` et
** que get_co n'existe pas — c'est voulu, il ecrit le contrat avant le code.
*/

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_element.h"

#include <stdio.h>
#include <string.h>

t_err	get_co(char *str, t_scene *sc);

typedef struct s_co_case
{
	const char	*input;
	t_err		expected_err;
	double		expected_diameter;
	double		expected_height;
	double		expected_size;
}	t_co_case;

static int	check_node(t_obj *o, t_co_case c)
{
	if (!o || o->id != cone)
		return (1);
	if (o->diameter != c.expected_diameter)
		return (1);
	if (o->height != c.expected_height)
		return (1);
	if (o->checker_size != c.expected_size)
		return (1);
	return (0);
}

static int	run_case(t_co_case c, int index)
{
	char		buf[160];
	t_scene		sc;
	t_err		err;
	int			nodes;
	int			bad;
	t_obj		*o;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_co(buf, &sc);
	nodes = 0;
	o = sc.obj_lst;
	while (o)
	{
		nodes++;
		o = o->next;
	}
	bad = (err != c.expected_err);
	if (!bad && err == ok)
		bad = (nodes != 1) || check_node(sc.obj_lst, c);
	printf("%-3d %-5s \"%-38s\" attendu=(%d, %.2f, %.2f, %.2f) obtenu=(%d, %.2f, %.2f, %.2f)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_diameter, c.expected_height, c.expected_size, (int)err,
		sc.obj_lst ? sc.obj_lst->diameter : 0.0,
		sc.obj_lst ? sc.obj_lst->height : 0.0,
		sc.obj_lst ? sc.obj_lst->checker_size : 0.0);
	free_obj(sc.obj_lst);
	return (bad);
}

int	main(void)
{
	static const t_co_case	cases[] = {
	{"0,0,0 0,1,0 2 3 255,0,0", ok, 2.0, 3.0, 0.0},
	{"0,0,0 0,1,0 2 3 255,0,0\n", ok, 2.0, 3.0, 0.0},
	{"-1,2,-3 0,1,1 1.5 4.25 12,34,56", ok, 1.5, 4.25, 0.0},
	{"0,0,0 0,1,0 2 3 255,0,0 0.8 60", ok, 2.0, 3.0, 0.0},
	{"0,0,0 0,1,0 2 3 255,0,0 0.8 60 0.5", ok, 2.0, 3.0, 0.5},
	{"0,0,0 0,1,0 2 3 255,0,0 0 0 0.5", ok, 2.0, 3.0, 0.5},
	{"0,0,0 0,1,0 2 3", bad_co_config, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 3 255,0,0 0.8", bad_co_config, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 3 255,0,0 0.8 60 0.5 1", bad_co_config, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 0 255,0,0", invalid_length_value, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 -3 255,0,0", invalid_length_value, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 0 3 255,0,0", invalid_length_value, 0.0, 0.0, 0.0},
	{"0,0,0 0,0,0 2 3 255,0,0", vector_null, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 3 300,0,0", invalid_color_value, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 3 255,0", bad_color_format, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 abc 3 255,0,0", invalid_double_value, 0.0, 0.0, 0.0},
	{"0,0,0 0,1,0 2 3 255,0,0 0 0 0", ok, 2.0, 3.0, 0.0},
	{NULL, ok, 0.0, 0.0, 0.0}
	};
	int						failures;
	int						i;

	failures = 0;
	i = 0;
	while (cases[i].input)
	{
		failures += run_case(cases[i], i);
		i++;
	}
	printf("\n%d cas en echec sur %d\n", failures, i);
	return (failures != 0);
}
