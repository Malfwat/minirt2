/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:45:00 by me                #+#    #+#             */
/*   Updated: 2026/11/13 17:45:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

t_err	get_sp(char *str, t_scene *sc);

/*
** La chaine testee est la partie champs de la ligne, identifiant deja
** consomme : "0,0,20 12.6 255,0,0", pas "sp 0,0,20 ...".
*/
typedef struct s_sp_case
{
	const char		*input;
	t_err			expected_err;
	double			expected_x;
	double			expected_diameter;
	int				expected_r;
	int				expected_nodes;
}	t_sp_case;

static int	check_node(t_obj *o, t_sp_case c)
{
	if (!o)
		return (1);
	if (o->coordinate.x != c.expected_x || o->diameter != c.expected_diameter)
		return (1);
	if (o->color.r != c.expected_r || o->id != sphere)
		return (1);
	return (0);
}

static int	run_case(t_sp_case c, int index)
{
	char	buf[160];
	t_scene	sc;
	t_err	err;
	int		nodes;
	int		bad;
	t_obj	*o;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_sp(buf, &sc);
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
	printf("%-3d %-5s \"%-26s\" attendu=(%d, noeuds %d) obtenu=(%d, noeuds %d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_nodes, (int)err, nodes);
	return (bad);
}

/* Deux spheres : la tete doit etre la derniere ajoutee. */
static int	test_chained_list(void)
{
	char	*a;
	char	*b;
	t_scene	sc;
	int		bad;

	memset(&sc, 0, sizeof(sc));
	a = strdup("0,0,20 12.6 255,0,0");
	b = strdup("5,5,5 2 1,2,3");
	bad = (get_sp(a, &sc) != ok || get_sp(b, &sc) != ok);
	if (!bad)
		bad = (!sc.obj_lst || !sc.obj_lst->next
			|| sc.obj_lst->coordinate.x != 5 || sc.obj_lst->diameter != 2);
	printf("%-3d %-5s \"deux spheres\" attendu=(tete = 5/2.00, 2 noeuds)\n",
		99, bad ? "FAIL" : "ok");
	free(a);
	free(b);
	return (bad);
}

int	main(void)
{
	static const t_sp_case	cases[] = {
	{"0,0,20 12.6 255,0,0", ok, 0, 12.6, 255, 1},
	{"0,0,20 12.6 255,0,0\n", ok, 0, 12.6, 255, 1},
	{"0,0,20 12.6 255, 0, 0", ok, 0, 12.6, 255, 1},
	{"-5.5,2,20.6 0.5 10,20,30 ", ok, -5.5, 0.5, 10, 1},
	{"0,0,20 0 255,0,0", invalid_length_value, 0, 0, 0, 0},
	{"0,0,20 -1 255,0,0", invalid_length_value, 0, 0, 0, 0},
	{"0,0,20 12.6 256,0,0", invalid_color_value, 0, 0, 0, 0},
	{"0,0,20 12.6 255,0", bad_color_format, 0, 0, 0, 0},
	{"0,0,20 12.6", bad_sp_config, 0, 0, 0, 0},
	{"0,0,20 12.6 255,0,0 extra", bad_sp_config, 0, 0, 0, 0},
	{"0, 0, 20 12.6 255,0,0", bad_vec_format, 0, 0, 0, 0},
	{"", bad_sp_config, 0, 0, 0, 0},
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
	failures += test_chained_list();
	printf("\n%d cas en echec sur %d\n", failures, i + 1);
	return (failures != 0);
}
