/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_light_comp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:41:00 by me                #+#    #+#             */
/*   Updated: 2026/11/12 21:41:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

t_err	get_light_comp(char *str, void **ptrs, getter *fptr);

/*
** La chaine testee est la partie champs de la ligne, identifiant deja
** consomme : "-40,0,30 0.6 255,255,255", pas "L -40,0,30 ...".
** L'ordre des composantes est celui de get_light_getter : vecteur,
** ratio, couleur.
*/
typedef struct s_light_case
{
	const char		*input;
	t_err			expected_err;
	double			expected_x;
	double			expected_ratio;
	int				expected_r;
}	t_light_case;

static int	run_case(t_light_case c, int index)
{
	char	buf[160];
	t_light	l;
	void	*ptrs[3];
	t_err	err;
	int		bad;

	memset(&l, 0, sizeof(l));
	ptrs[0] = &l.coordinate;
	ptrs[1] = &l.ratio;
	ptrs[2] = &l.color;
	strcpy(buf, c.input);
	err = get_light_comp(buf, ptrs, get_light_getter());
	bad = (err != c.expected_err);
	if (!bad && err == ok)
	{
		if (l.coordinate.x != c.expected_x || l.ratio != c.expected_ratio
			|| l.color.r != c.expected_r)
			bad = 1;
	}
	printf("%-3d %-5s \"%-26s\" attendu=(%d, %.2f/%.2f/%d) obtenu=(%d, %.2f/%.2f/%d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err, c.expected_x,
		c.expected_ratio, c.expected_r, (int)err, l.coordinate.x, l.ratio,
		l.color.r);
	return (bad);
}

int	main(void)
{
	static const t_light_case	cases[] = {
	{"-40,0,30 0.6 255,255,255", ok, -40, 0.6, 255},
	{"-40,0,30 0.6 255,255,255\n", ok, -40, 0.6, 255},
	{"-40,0,30 0.6 255, 0, 255", ok, -40, 0.6, 255},
	{"0,0,0 1 10,0,255 ", ok, 0, 1.0, 10},
	{"-40,0,30 1.5 255,0,0", bad_ratio_format, 0, 0, 0},
	{"-40,0,30 0.6 256,0,0", invalid_color_value, 0, 0, 0},
	{"-40,0,30 0.6 255,0", bad_color_format, 0, 0, 0},
	{"-40,0,30 0.6", bad_light_config, 0, 0, 0},
	{"", bad_vec_format, 0, 0, 0},
	{NULL, ok, 0, 0, 0}
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
