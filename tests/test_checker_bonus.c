/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_checker_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 12:20:00 by me                #+#    #+#             */
/*   Updated: 2026/11/24 12:45:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_element.h"

#include <stdio.h>
#include <string.h>

t_err	get_pl(char *str, t_scene *sc);

/*
** Champ optionnel de taille de cellule du damier, sur la ligne pl.
** Il vient APRES les deux champs de speculaire :
**
**   "0,0,-10 0,1,0 255,0,225"            3 champs  pas de damier
**   "0,0,-10 0,1,0 255,0,225 0.8 60"     5 champs  speculaire seul
**   "0,0,-10 0,1,0 255,0,225 0.8 60 2.5" 6 champs  speculaire + damier
**   "0,0,-10 0,1,0 255,0,225 0 0 2.5"    6 champs  damier seul, speculaire nul
**
** Present, la taille doit etre STRICTEMENT positive. Une chaine non numerique
** donne invalid_double_value, une valeur nulle ou negative donne
** negative : invalid_length_value. Zero : pas de damier. Absente : 0 aussi.
** Quatre champs, ou sept, sont refuses.
*/

typedef struct s_ck_case
{
	const char	*input;
	t_err		expected_err;
	double		expected_size;
	double		expected_intensity;
	int			expected_nodes;
}	t_ck_case;

static int	check_node(t_obj *o, t_ck_case c)
{
	if (!o || o->id != plan)
		return (1);
	if (o->checker_size != c.expected_size)
		return (1);
	if (o->intensity != c.expected_intensity)
		return (1);
	return (0);
}

static int	run_case(t_ck_case c, int index)
{
	char		buf[160];
	t_scene		sc;
	t_err		err;
	int			nodes;
	int			bad;
	t_obj		*o;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_pl(buf, &sc);
	nodes = 0;
	o = sc.obj_lst;
	while (o)
	{
		nodes++;
		o = o->next;
	}
	bad = (err != c.expected_err);
	if (!bad && err == ok)
		bad = (nodes != c.expected_nodes) || check_node(sc.obj_lst, c);
	printf("%-3d %-5s \"%-34s\" attendu=(%d, %.3f, %.2f, %d) obtenu=(%d, %.3f, %.2f, %d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_size, c.expected_intensity, c.expected_nodes, (int)err,
		sc.obj_lst ? sc.obj_lst->checker_size : 0.0,
		sc.obj_lst ? sc.obj_lst->intensity : 0.0, nodes);
	free_obj(sc.obj_lst);
	return (bad);
}

int	main(void)
{
	static const t_ck_case	cases[] = {
	{"0,0,-10 0,1,0 255,0,225", ok, 0.0, 0.0, 1},
	{"0,0,-10 0,1,0 255,0,225 0.8 60", ok, 0.0, 0.8, 1},
	{"0,0,-10 0,1,0 255,0,225 0.8 60 2.5", ok, 2.5, 0.8, 1},
	{"0,0,-10 0,1,0 255,0,225 0 0 2.5", ok, 2.5, 0.0, 1},
	{"0,0,-10 0,1,0 255,0,225 0 0 0.001", ok, 0.001, 0.0, 1},
	{"0,0,-10 0,1,0 255,0,225 0 0 2.5\n", ok, 2.5, 0.0, 1},
	{"0,0,-10 0,1,0 255,0,225 0 0 0", ok, 0.0, 0.0, 1},
	{"0,0,-10 0,1,0 255,0,225 0 0 -1", invalid_length_value, 0.0, 0.0, 0},
	{"0,0,-10 0,1,0 255,0,225 0 0 abc", invalid_double_value, 0.0, 0.0, 0},
	{"0,0,-10 0,1,0 255,0,225 0.8", bad_pl_config, 0.0, 0.0, 0},
	{"0,0,-10 0,1,0 255,0,225 0 0 1 2", bad_ppm_config, 0.0, 0.0, 0},
	{"0,0,-10 0,0,0 255,0,225 0 0 2", vector_null, 0.0, 0.0, 0},
	{"0,0,-10 0,1,0 300,0,0 0 0 2", invalid_color_value, 0.0, 0.0, 0},
	{NULL, ok, 0.0, 0.0, 0}
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
