/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 15:05:00 by me                #+#    #+#             */
/*   Updated: 2026/11/13 15:05:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

t_err	get_light(char *str, t_scene *sc);

/*
** La chaine testee est la partie champs de la ligne, identifiant deja
** consomme : "-40,0,30 0.6 255,255,255", pas "L -40,0,30 ...".
*/
typedef struct s_light_line
{
	const char		*input;
	t_err			expected_err;
	double			expected_x;
	double			expected_ratio;
	int				expected_r;
	int				expected_nodes;
}	t_light_line;

static int	check_node(t_light *l, t_light_line c)
{
	if (!l)
		return (1);
	if (l->coordinate.x != c.expected_x || l->ratio != c.expected_ratio)
		return (1);
	if (l->color.r != c.expected_r)
		return (1);
	return (0);
}

static int	run_case(t_light_line c, int index)
{
	char	buf[160];
	t_scene	sc;
	t_err	err;
	int		nodes;
	int		bad;
	t_light	*l;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_light(buf, &sc);
	nodes = 0;
	l = sc.light_lst;
	while (l)
	{
		nodes++;
		l = l->next;
	}
	bad = (err != c.expected_err);
	if (!bad && err == ok)
	{
		bad = (nodes != c.expected_nodes) || check_node(sc.light_lst, c);
	}
	printf("%-3d %-5s \"%-26s\" attendu=(%d, noeuds %d) obtenu=(%d, noeuds %d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_nodes, (int)err, nodes);
	return (bad);
}

/* Deux ajouts successifs : la tete doit etre la derniere lumiere ajoutee. */
static int	test_chained_list(void)
{
	char	*a;
	char	*b;
	t_scene	sc;
	t_err	err;
	t_light	*l;
	int		bad;

	memset(&sc, 0, sizeof(sc));
	a = strdup("-40,0,30 0.6 255,255,255");
	b = strdup("10,10,10 0.3 1,2,3");
	err = get_light(a, &sc);
	if (err == ok)
		err = get_light(b, &sc);
	l = sc.light_lst;
	bad = (err != ok || !l || !l->next);
	if (!bad)
	{
		bad = (l->coordinate.x != 10 || l->ratio != 0.3 || l->color.r != 1);
		if (bad)
			printf("FAIL  tete de liste inattendue : x=%.1f ratio=%.2f r=%d\n",
				l->coordinate.x, l->ratio, l->color.r);
	}
	printf("%-3d %-5s \"deux ajouts\" attendu=(tete = 10/0.30/1, 2 noeuds)\n",
		99, bad ? "FAIL" : "ok");
	free(a);
	free(b);
	return (bad);
}

int	main(void)
{
	static const t_light_line	cases[] = {
	{"-40,0,30 0.6 255,255,255", ok, -40, 0.6, 255, 1},
	{"-40,0,30 0.6 255,255,255\n", ok, -40, 0.6, 255, 1},
	{"-40,0,30 0.6 255, 0, 255", ok, -40, 0.6, 255, 1},
	{"0,0,0 1 10,0,255 ", ok, 0, 1.0, 10, 1},
	{"-40,0,30 1.5 255,0,0", bad_ratio_format, 0, 0, 0, 0},
	{"-40,0,30 0.6 256,0,0", invalid_color_value, 0, 0, 0, 0},
	{"-40,0,30 0.6 255,0", bad_color_format, 0, 0, 0, 0},
	{"-40,0,30 0.6", bad_light_config, 0, 0, 0, 0},
	{"-40,0,30 0.6 255,0,0 extra", bad_light_config, 0, 0, 0, 0},
	{"-40, 0, 30 0.6 255,255,255", bad_vec_format, 0, 0, 0, 0},
	{"-40,0,30 0.6 255 ,0,255", invalid_color_value, 0, 0, 0, 0},
	{"", bad_light_config, 0, 0, 0, 0},
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
