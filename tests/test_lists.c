/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lists.c                                       
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_element.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"
#include "str.h"

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

static int	count_obj(t_obj *o)
{
	int	n;

	n = 0;
	while (o)
	{
		n++;
		o = o->next;
	}
	return (n);
}

static int	count_light(t_light *l)
{
	int	n;

	n = 0;
	while (l)
	{
		n++;
		l = l->next;
	}
	return (n);
}

int	main(void)
{
	t_scene	sc;
	t_obj	o;
	t_light	*lst;
	t_light	l;

	ft_bzero(&sc, sizeof(sc));
	ft_bzero(&o, sizeof(o));
	o.id = sphere;
	o.diameter = 1;
	check(add_obj(&sc, o) == ok, "add_obj 1");
	o.diameter = 2;
	check(add_obj(&sc, o) == ok, "add_obj 2");
	o.diameter = 3;
	check(add_obj(&sc, o) == ok, "add_obj 3");
	check(count_obj(sc.obj_lst) == 3, "3 objets dans la liste");
	check(sc.obj_lst->diameter == 3, "tete = dernier ajoute");
	o.id = plan;
	check(add_obj(&sc, o) == ok, "add_obj plan");
	check(count_obj(sc.obj_lst) == 4 && sc.obj_lst->id == plan, "plan en tete");
	lst = NULL;
	ft_bzero(&l, sizeof(l));
	l.ratio = 0.5;
	check(add_light(&lst, l) == true, "add_light 1");
	l.ratio = 0.7;
	check(add_light(&lst, l) == true, "add_light 2");
	check(count_light(lst) == 2, "2 lumieres");
	check(lst->ratio == 0.7, "tete = derniere lumiere");
	free_obj(sc.obj_lst);
	free_light(lst);
	free_obj(NULL);
	free_light(NULL);
	check(1, "free sur NULL ne crash pas");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
