/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_ratio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:43:32 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:45:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"

#include <stdio.h>
#include <string.h>

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

static t_err	try(char *input, double *res)
{
	char	buf[32];

	strcpy(buf, input);
	*res = -1;
	return (get_ratio(buf, res));
}

int	main(void)
{
	double	res;

	check(try("0.5", &res) == ok && res == 0.5, "0.5 accepte et vaut 0.5");
	check(try("1", &res) == ok && res == 1.0, "1 accepte, borne haute");
	check(try("0", &res) == ok && res == 0.0, "0 accepte, borne basse");
	check(try("0.25", &res) == ok && res == 0.25, "0.25 accepte");
	check(try("1.1", &res) == bad_ratio_format, "1.1 refuse, hors borne haute");
	check(try("-0.1", &res) == bad_ratio_format, "-0.1 refuse, hors borne basse");
	check(try("abc", &res) == bad_ratio_format, "abc refuse, pas un nombre");
	check(try("", &res) == bad_ratio_format, "chaine vide refusee");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
