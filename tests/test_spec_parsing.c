/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spec_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 20:50:00 by me                #+#    #+#             */
/*   Updated: 2026/11/19 20:50:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Suite de verification du champ speculaire (intensite + exposant) sur sp/pl/cy.
**
** Contrat teste :
**   - 3 champs  -> objet mat, intensite = 0, exposant = 0
**   - 5 champs  -> valide, valeurs stockees
**   - 4 champs  -> REJET (les deux ou aucun)
**   - 6 champs  -> rejet (contenu residuel)
**   - intensite hors [0,1] -> rejet ; exposant 0 accepte (sentinelle "mat"),
**     exposant negatif ou > 1000 -> rejet
**
** Compilation : le comportement differe entre les deux binaires.
**   mandatory : gcc ... tests/test_spec_parsing.c $MANDATORY_SRCS
**   bonus     : gcc -DTEST_BONUS ... tests/test_spec_parsing.c $BONUS_SRCS
**
** Les cas marques `extra = 1` sont acceptes par le bonus et refuses par le
** mandatory ; la table n'ecrit l'attente qu'une fois.
**
** Le code de sortie est le nombre d'echecs, pour pouvoir bloquer un commit.
*/

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

#ifdef TEST_BONUS
# define IS_BONUS 1
#else
# define IS_BONUS 0
#endif

#define ANY_ERR ((t_err)-1)

t_err	get_sp(char *str, t_scene *sc);

typedef struct s_case
{
	const char	*input;
	t_err		expected_err;
	int			extra;
	double		expected_intensity;
	double		expected_exposant;
	int			expected_nodes;
}	t_case;

static int	close_enough(double a, double b)
{
	double	d;

	d = a - b;
	if (d < 0)
		d = -d;
	return (d < 1e-6);
}

static int	check_node(t_obj *o, t_case c)
{
	if (!o)
		return (1);
	if (!close_enough(o->intensity, c.expected_intensity))
		return (1);
	if (!close_enough(o->exposant, c.expected_exposant))
		return (1);
	return (0);
}

static int	run_case(t_case c, int index)
{
	char	buf[160];
	t_scene	sc;
	t_err	err;
	t_err	wanted;
	int		nodes;
	int		bad;
	t_obj	*o;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_sp(buf, &sc);
	wanted = c.expected_err;
	if (c.extra && !IS_BONUS && wanted == ok)
		wanted = bad_sp_config;
	nodes = 0;
	o = sc.obj_lst;
	while (o)
	{
		nodes++;
		o = o->next;
	}
	if (wanted == ANY_ERR)
		bad = (err == ok);
	else
		bad = (err != wanted);
	if (!bad && err == ok)
		bad = (nodes != c.expected_nodes) || check_node(sc.obj_lst, c);
	printf("%-3d %-5s \"%-38s\" attendu=%4d obtenu=%4d (i=%.2f e=%.2f)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)wanted, (int)err,
		sc.obj_lst ? sc.obj_lst->intensity : 0.0,
		sc.obj_lst ? sc.obj_lst->exposant : 0.0);
	return (bad);
}

int	main(void)
{
	static const t_case	cases[] = {
	{"0,0,20 12.6 255,0,0", ok, 0, 0, 0, 1},
	{"0,0,20 12.6 255,0,0\n", ok, 0, 0, 0, 1},
	{"0,0,20 12.6 255,0,0 0.5 40", ok, 1, 0.5, 40, 1},
	{"0,0,20 12.6 255,0,0 0.5 40\n", ok, 1, 0.5, 40, 1},
	{"0,0,20 12.6 255,0,0 1 1000", ok, 1, 1, 1000, 1},
	{"0,0,20 12.6 255,0,0 0.5", ANY_ERR, 1, 0, 0, 0},
	{"0,0,20 12.6 255,0,0 0.5 40 9", bad_sp_config, 0, 0, 0, 0},
	{"0,0,20 12.6", bad_sp_config, 0, 0, 0, 0},
	{"0,0,20", bad_sp_config, 0, 0, 0, 0},
	{"", bad_sp_config, 0, 0, 0, 0},
	{"0,0,20 12.6 255,0,0 1.5 40", ANY_ERR, 1, 0, 0, 0},
	{"0,0,20 12.6 255,0,0 0.5 0", ok, 1, 0.5, 0, 1},
	{"0,0,20 12.6 255,0,0 0.5 1001", ANY_ERR, 1, 0, 0, 0},
	{"0,0,20 12.6 255,0,0 0.5 -40", ANY_ERR, 1, 0, 0, 0},
	{"0,0,20 12.6 255,0,0 abc 40", ANY_ERR, 1, 0, 0, 0},
	{NULL, ok, 0, 0, 0, 0}
	};
	int					failures;
	int					i;

	printf("== binaire %s ==\n\n", IS_BONUS ? "BONUS" : "MANDATORY");
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
