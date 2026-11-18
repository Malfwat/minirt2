/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 22:30:00 by me                #+#    #+#             */
/*   Updated: 2026/11/18 22:30:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_math.h"

#include <math.h>
#include <stdio.h>

/* a retirer quand rt_math.h declarera ces prototypes */
double	min(double a, double b);
bool	min_pos(double a, double b, double *t);
bool	quad(t_quad q, double *s1, double *s2);
bool	solve_hit(t_quad q, double *t);

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

static void	hit(const char *what, double a, double b, double c,
		int expected, double expected_t)
{
	t_quad	q;
	double	t;
	int		got;

	q.a = a;
	q.b = b;
	q.c = c;
	t = -999.0;
	got = solve_hit(q, &t);
	if (expected)
		check(got == 1 && fabs(t - expected_t) < 1e-9, what);
	else
		check(got == 0, what);
}

int	main(void)
{
	hit("deux racines positives 3 et 7", 1, -10, 21, 1, 3.0);
	hit("camera dans la sphere (-1 et 3)", 1, -2, -3, 1, 3.0);
	hit("les deux racines negatives", 1, 10, 21, 0, 0);
	hit("delta nul, racine -1", 1, 2, 1, 0, 0);
	hit("delta nul, racine 1", 1, -2, 1, 1, 1.0);
	hit("a negatif, racines -1 et 1", -1, 0, 1, 1, 1.0);
	hit("discriminant negatif", 1, 0, 1, 0, 0);
	hit("racine nulle : pas une intersection", 1, 0, 0, 0, 0);
	hit("sphere a 10 de rayon 1 (9 et 11)", 1, -20, 99, 1, 9.0);
	hit("sphere tangente (racine 10)", 1, -20, 100, 1, 10.0);
	check(min(3, 7) == 3 && min(7, 3) == 3, "min rend le plus petit");
	check(min_pos(-5, 2, &(double){0}) == true, "min_pos accepte la positive");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
