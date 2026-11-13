/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:51:11 by me                #+#    #+#             */
/*   Updated: 2026/11/14 00:01:37 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

t_err	parse_line(char *str, t_scene *sc)
{
	t_elem		elem;
	t_err		err;

	err = get_and_pass_elem(&str, &elem);
	if (err != ok)
		return (err);
	sc->actual = elem;
	if (sc->camera && elem == cam)
		return (dup_cam);
	if (sc->ambient && elem == amb)
		return (dup_amb);
	if (sc->l && elem == light)
		return (dup_light);
	set_bool(&sc->l, &sc->camera, &sc->ambient, elem);
	return (get_parsefunc(elem)(str, sc));
}
