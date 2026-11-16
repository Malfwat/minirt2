/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_math.c */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"
#include "rt_struct.h"

#include <math.h>
#include <stdio.h>

static int	g_fail;
static int	g_total;

static void	check(int cond, const char *what)
{
	g_total++;
	if (!cond)
	{
		g_fail++;
		printf("FAIL  %s\n", what);
	}
}

static int	near(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

int	main(void)
{
	t_vec3	v;
	t_vec3	r;

	v.x = 3;
	v.y = 4;
	v.z = 0;
	check(near(get_norme(v), 5.0), "norme 3-4-0 = 5");
	r = normalize(v);
	check(near(r.x, 0.6) && near(r.y, 0.8) && near(r.z, 0), "normalize 3-4-0");
	v.x = 0;
	v.y = 0;
	v.z = 0;
	check(near(get_norme(v), 0.0), "norme vecteur nul = 0");
	v.x = 0;
	v.y = 0;
	v.z = 5;
	r = normalize(v);
	check(near(r.x, 0) && near(r.y, 0) && near(r.z, 1), "normalize 0-0-5");
	v.x = -2;
	v.y = 0;
	v.z = 0;
	r = normalize(v);
	check(near(r.x, -1) && near(r.y, 0) && near(r.z, 0), "normalize -2-0-0");
	v.x = 0.7071;
	v.y = 0.7071;
	v.z = 0;
	check(fabs(get_norme(v) - 1.0) < 1e-4, "norme 0.7071x2 proche de 1");
	r = normalize(v);
	check(fabs(get_norme(r) - 1.0) < 1e-9, "normalize rend une norme exactement 1");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
