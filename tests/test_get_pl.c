/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_pl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:35:00 by me                #+#    #+#             */
/*   Updated: 2026/11/13 23:35:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

t_err	get_pl(char *str, t_scene *sc);

/*
** Partie champs de la ligne, identifiant deja consomme :
** "0,0,-10 0,1,0 255,0,225", pas "pl 0,0,-10 ...".
*/
typedef struct s_pl_case
{
	const char		*input;
	t_err			expected_err;
	double			expected_x;
	double			expected_nz;
	int				expected_r;
	int				expected_nodes;
}	t_pl_case;

static int	check_node(t_obj *o, t_pl_case c)
{
	if (!o)
		return (1);
	if (o->id != plan)
		return (1);
	if (o->coordinate.x != c.expected_x || o->vec.z != c.expected_nz)
		return (1);
	if (o->color.r != c.expected_r)
		return (1);
	return (0);
}

static int	run_case(t_pl_case c, int index)
{
	char	buf[160];
	t_scene	sc;
	t_err	err;
	int		nodes;
	int		bad;
	t_obj	*o;

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
	printf("%-3d %-5s \"%-28s\" attendu=(%d, noeuds %d) obtenu=(%d, noeuds %d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_nodes, (int)err, nodes);
	return (bad);
}

int	main(void)
{
	static const t_pl_case	cases[] = {
	{"0,0,-10 0,1,0 255,0,225", ok, 0, 0, 255, 1},
	{"0,0,-10 0,1,0 255,0,225\n", ok, 0, 0, 255, 1},
	{"0,0,-10 0,1,0 255, 0, 225", ok, 0, 0, 255, 1},
	{"-5.5,2,3 0,0,-1 10,20,30 ", ok, -5.5, -1, 10, 1},
	{"0,0,-10 0,1,0", bad_pl_config, 0, 0, 0, 0},
	{"0,0,-10 0,1,0 255,0,225 extra", bad_pl_config, 0, 0, 0, 0},
	{"", bad_pl_config, 0, 0, 0, 0},
	{"0,0,-10 0, 1, 0 255,0,225", bad_vec_format, 0, 0, 0, 0},
	{"0,0,-10 0,1,0 256,0,0", invalid_color_value, 0, 0, 0, 0},
	{"0,0,-10 0,1,0 255,0", bad_color_format, 0, 0, 0, 0},
	{NULL, ok, 0, 0, 0, 0}
	};
	int	failures;
	int	i;

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
