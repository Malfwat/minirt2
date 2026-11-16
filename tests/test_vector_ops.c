/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 00:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/17 00:04:26 by me               ###   ########.fr       */
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

static t_vec3	v(double x, double y, double z)
{
	t_vec3	r;

	r.x = x;
	r.y = y;
	r.z = z;
	return (r);
}

static int	same(t_vec3 a, t_vec3 b)
{
	return (fabs(a.x - b.x) < 1e-9 && fabs(a.y - b.y) < 1e-9
		&& fabs(a.z - b.z) < 1e-9);
}

int	main(void)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	r;

	a = v(1, 2, 3);
	b = v(4, 5, 6);
	check(same(add(a, b), v(5, 7, 9)), "add 1,2,3 + 4,5,6");
	check(same(sub(a, b), v(-3, -3, -3)), "sub 1,2,3 - 4,5,6");
	check(same(mult(a, 2), v(2, 4, 6)), "mult par 2");
	check(same(mult(a, 0), v(0, 0, 0)), "mult par 0");
	check(same(mult(a, -1), v(-1, -2, -3)), "mult par -1");
	check(scal(v(1, 0, 0), v(0, 1, 0)) == 0, "scal orthogonaux = 0");
	check(scal(v(1, 2, 3), v(1, 2, 3)) == 14, "scal avec lui-meme = 14");
	check(scal(v(0, 1, 0), v(0, -1, 0)) == -1, "scal opposes = -1");
	r = cross(v(1, 0, 0), v(0, 1, 0));
	check(same(r, v(0, 0, 1)), "cross x^y = z");
	r = cross(v(0, 1, 0), v(1, 0, 0));
	check(same(r, v(0, 0, -1)), "cross y^x = -z (antisymetrie)");
	r = cross(v(2, 0, 0), v(0, 3, 0));
	check(fabs(get_norme(r) - 1.0) < 1e-12, "cross normalise (entrees 2 et 3)");
	check(same(cross(v(1, 0, 0), v(1, 0, 0)), v(0, 0, 1)) == 0,
		"cross de deux colineaires ne donne pas un axe valide");
	r = cross(v(0, 1, 0), v(0, 1, 0));
	check(!isfinite(r.x) || !isfinite(r.y) || !isfinite(r.z),
		"cross de deux colineaires -> NaN (contrat a garder en tete)");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
