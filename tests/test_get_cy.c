/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_cy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:40:00 by me                #+#    #+#             */
/*   Updated: 2026/11/13 23:40:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

t_err	get_cy(char *str, t_scene *sc);

/*
** Partie champs de la ligne, identifiant deja consomme :
** "50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255", pas "cy ...".
** Ordre : centre, axe, diametre, hauteur, couleur.
*/
typedef struct s_cy_case
{
	const char		*input;
	t_err			expected_err;
	double			expected_x;
	double			expected_diameter;
	double			expected_height;
	int				expected_r;
	int				expected_nodes;
}	t_cy_case;

static int	check_node(t_obj *o, t_cy_case c)
{
	if (!o)
		return (1);
	if (o->id != cylinder)
		return (1);
	if (o->coordinate.x != c.expected_x || o->diameter != c.expected_diameter
		|| o->height != c.expected_height)
		return (1);
	if (o->color.r != c.expected_r)
		return (1);
	return (0);
}

static int	run_case(t_cy_case c, int index)
{
	char	buf[180];
	t_scene	sc;
	t_err	err;
	int		nodes;
	int		bad;
	t_obj	*o;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_cy(buf, &sc);
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
	printf("%-3d %-5s \"%-30s\" attendu=(%d, noeuds %d) obtenu=(%d, noeuds %d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_nodes, (int)err, nodes);
	return (bad);
}

int	main(void)
{
	static const t_cy_case	cases[] = {
	{"50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255", ok, 50, 14.2, 21.42, 10, 1},
	{"50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255\n", ok, 50, 14.2, 21.42, 10, 1},
	{"50.0,0.0,20.6 0,0,1.0 14.2 21.42 10, 0, 255", ok, 50, 14.2, 21.42, 10, 1},
	{"0,0,0 0,0,1 2 3 255,255,255 ", ok, 0, 2, 3, 255, 1},
	{"50.0,0.0,20.6 0,0,1.0 14.2 21.42", bad_cy_config, 0, 0, 0, 0, 0},
	{"50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255 x", bad_cy_config, 0, 0, 0, 0, 0},
	{"", bad_cy_config, 0, 0, 0, 0, 0},
	{"50.0,0.0,20.6 0,0,1.0 0 21.42 10,0,255", invalid_length_value, 0, 0, 0, 0, 0},
	{"50.0,0.0,20.6 0,0,1.0 14.2 0 10,0,255", invalid_length_value, 0, 0, 0, 0, 0},
	{"50.0,0.0,20.6 0,0,1.0 14.2 21.42 256,0,0", invalid_color_value, 0, 0, 0, 0, 0},
	{"50.0,0.0,20.6 0, 0, 1.0 14.2 21.42 10,0,255", bad_vec_format, 0, 0, 0, 0, 0},
	{NULL, ok, 0, 0, 0, 0, 0}
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
