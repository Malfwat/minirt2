/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 15:22:00 by me                #+#    #+#             */
/*   Updated: 2026/11/13 15:22:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

t_err	get_cam(char *str, t_scene *sc);

/*
** La chaine testee est la partie champs de la ligne, identifiant deja
** consomme : "-50,0,20 0,0,1 70", pas "C -50,0,20 ...".
*/
typedef struct s_cam_case
{
	const char		*input;
	t_err			expected_err;
	double			expected_x;
	double			expected_fov;
}	t_cam_case;

static int	run_case(t_cam_case c, int index)
{
	char	buf[160];
	t_scene	sc;
	t_err	err;
	int		bad;

	memset(&sc, 0, sizeof(sc));
	strcpy(buf, c.input);
	err = get_cam(buf, &sc);
	bad = (err != c.expected_err);
	if (!bad && err == ok)
	{
		if (sc.cam.coordinate.x != c.expected_x
			|| sc.cam.fov != (__UINT8_TYPE__)c.expected_fov)
			bad = 1;
	}
	printf("%-3d %-5s \"%-26s\" attendu=(%d, x=%.1f fov=%d) obtenu=(%d, x=%.1f fov=%d)\n",
		index, bad ? "FAIL" : "ok", c.input, (int)c.expected_err,
		c.expected_x, (int)c.expected_fov, (int)err, sc.cam.coordinate.x,
		(int)sc.cam.fov);
	return (bad);
}

int	main(void)
{
	static const t_cam_case	cases[] = {
	{"-50,0,20 0,0,1 70", ok, -50, 70},
	{"-50,0,20 0,0,1 70\n", ok, -50, 70},
	{"0,0,0 -1,0,0 180", ok, 0, 180},
	{"1.5,2.5,-3.5 0.6,0.8,0 90", ok, 1.5, 90},
	{"-50,0,20 0,0,1 0", ok, -50, 0},
	{"-50,0,20 0,0,1 200", bad_fov_format, 0, 0},
	{"-50,0,20 0,0,1 -1", bad_fov_format, 0, 0},
	{"-50,0,20 0,0,1 70 extra", bad_cam_config, 0, 0},
	{"-50,0,20 0,0,1", bad_cam_config, 0, 0},
	{"-50, 0, 20 0,0,1 70", bad_vec_format, 0, 0},
	{"-50,0 0,0,1 70", bad_vec_format, 0, 0},
	{"", bad_cam_config, 0, 0},
	{NULL, ok, 0, 0}
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
