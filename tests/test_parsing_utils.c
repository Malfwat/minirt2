/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing_utils.c                               
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

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

t_elem	get_elem(char *line);
void	pass_elem(char **str_ptr);

static int	ends_on(const char *str, const char *tail)
{
	return (strcmp(str, tail) == 0);
}

int	main(void)
{
	char	buf[64];
	char	out[64];
	char	*s;
	t_elem	elem;
	t_err	err;
	double	d;

	check(is_line_empty("") && is_line_empty("\n") && is_line_empty("   "), "ligne vide");
	check(is_line_empty("\t\r\n") && !is_line_empty("a"), "ligne blanche et non vide");
	strcpy(buf, "70\n");
	null_terminate_component(buf);
	check(ends_on(buf, "70"), "null_terminate coupe sur \\n");
	strcpy(buf, "70");
	null_terminate_component(buf);
	check(ends_on(buf, "70"), "null_terminate sans blanc");
	strcpy(buf, "70 ab");
	null_terminate_component(buf);
	check(ends_on(buf, "70"), "null_terminate coupe sur espace");
	strcpy(out, "70 ab");
	s = out;
	pass_elem(&s);
	check(ends_on(s, "ab"), "pass_elem avance au composant suivant");
	strcpy(out, "70\n");
	s = out;
	pass_elem(&s);
	check(*s == 0, "pass_elem fin de ligne -> fin de chaine");
	strcpy(out, "70 \n");
	s = out;
	pass_elem(&s);
	check(*s == 0, "pass_elem espace avant \\n -> fin de chaine");
	check(get_elem("sp") == sphere && get_elem("pl") == plan, "get_elem sp et pl");
	check(get_elem("cy") == cylinder && get_elem("A") == amb, "get_elem cy et A");
	check(get_elem("L") == light && get_elem("C") == cam, "get_elem L et C");
	check(get_elem("zz") == none && get_elem("spx") == none, "get_elem inconnu");
	strcpy(out, "sp 0,0,1");
	s = out;
	err = get_and_pass_elem(&s, &elem);
	check(err == ok && elem == sphere && ends_on(s, "0,0,1"), "get_and_pass_elem sp");
	strcpy(out, "zz 1");
	s = out;
	check(get_and_pass_elem(&s, &elem) == bad_elem, "get_and_pass_elem inconnu");
	check(get_parsefunc(sphere) == get_sp, "parsefunc sphere");
	check(get_parsefunc(plan) == get_pl, "parsefunc plan");
	check(get_parsefunc(cylinder) == get_cy, "parsefunc cylinder");
	check(get_parsefunc(none) == get_pl, "parsefunc none retombe sur get_pl (defaut)");
	d = 0;
	strcpy(out, "12.6");
	check(get_diameter(out, &d) == ok && d == 12.6, "diameter 12.6");
	strcpy(out, "0");
	check(get_diameter(out, &d) == invalid_length_value, "diameter 0 refuse");
	strcpy(out, "-1");
	check(get_diameter(out, &d) == invalid_length_value, "diameter -1 refuse");
	strcpy(out, "21.42");
	check(get_height(out, &d) == ok && d == 21.42, "height 21.42");
	strcpy(out, "-0.5");
	check(get_height(out, &d) == invalid_length_value, "height negatif refuse");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
