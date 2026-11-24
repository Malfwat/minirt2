/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:51:11 by me                #+#    #+#             */
/*   Updated: 2026/11/25 00:14:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "str.h"

t_elem	get_elem(char *line)
{
	if (!ft_strcmp((line), AMB))
		return (amb);
	if (!ft_strcmp((line), CAM))
		return (cam);
	if (!ft_strcmp((line), LIGHT))
		return (light);
	if (!ft_strcmp((line), PL))
		return (plan);
	if (!ft_strcmp((line), CY))
		return (cylinder);
	if (!ft_strcmp((line), SP))
		return (sphere);
	if (!ft_strcmp((line), CO))
		return (cone);
	return (none);
}

t_parse_functions	get_parsefunc(t_elem elem)
{
	if (elem == amb)
		return (get_amb);
	if (elem == light)
		return (get_light);
	if (elem == cam)
		return (get_cam);
	if (elem == sphere)
		return (get_sp);
	if (elem == cylinder)
		return (get_cy);
	if (elem == plan)
		return (get_pl);
	return (get_co);
}

t_err	parse_line(char *str, t_scene *sc)
{
	t_elem		elem;
	t_err		err;

	err = get_and_pass_elem(&str, &elem);
	if (err != ok)
		return (err);
	if (sc->camera && elem == cam)
		return (dup_cam);
	if (sc->ambient && elem == amb)
		return (dup_amb);
	set_bool(&sc->l, &sc->camera, &sc->ambient, elem);
	return (get_parsefunc(elem)(str, sc));
}
