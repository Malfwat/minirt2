/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_amb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:32:00 by me                #+#    #+#             */
/*   Updated: 2026/11/12 21:32:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"

#include <stdio.h>
#include <string.h>

t_err	get_amb(char *str, t_scene *sc);

/*
** La chaine testee est la partie champs de la ligne, identifiant deja
** consomme par get_and_pass_elem : "0.2 255,255,255", pas "A 0.2 ...".
*/
typedef struct s_amb_case
{
	const char		*input;
	t_err			expected_err;
	double			expected_ratio;
	int				expected_r;
	int				expected_g;
	int				expected_b;
}	t_amb_case;

static int	run_case(t_amb_case c, int index)
{
	char	buf[128];
	t_scene	sc;
	t_err	err;
	int		bad;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_amb(buf, &sc);
	bad = (err != c.expected_err);
	if (!bad && err == ok)
	{
		if (sc.amb.ratio != c.expected_ratio)
			bad = 1;
		if (sc.amb.color.r != c.expected_r || sc.amb.color.g != c.expected_g
			|| sc.amb.color.b != c.expected_b)
			bad = 1;
	}
	printf("%-3d %-5s \"%-20s\" attendu=(%d, %.2f, %d/%d/%d) obtenu=(%d, %.2f, %d/%d/%d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_ratio, c.expected_r, c.expected_g, c.expected_b,
		(int)err, sc.amb.ratio, sc.amb.color.r, sc.amb.color.g,
		sc.amb.color.b);
	return (bad);
}

int	main(void)
{
	static const t_amb_case	cases[] = {
	{"0.2 255,255,255", ok, 0.2, 255, 255, 255},
	{"0.2 255, 255, 255", ok, 0.2, 255, 255, 255},
	{"0.2 255,255,255\n", ok, 0.2, 255, 255, 255},
	{"0.2 10,0,255 ", ok, 0.2, 10, 0, 255},
	{"0 0,0,0", ok, 0.0, 0, 0, 0},
	{"1 255,255,255", ok, 1.0, 255, 255, 255},
	{"1.5 255,0,0", bad_ratio_format, 0, 0, 0, 0},
	{"0.2 256,0,0", invalid_color_value, 0, 0, 0, 0},
	{"0.2 255,0", bad_color_format, 0, 0, 0, 0},
	{"0.2", bad_amb_config, 0, 0, 0, 0},
	{"0.2 255,0,0 extra", bad_amb_config, 0, 0, 0, 0},
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
