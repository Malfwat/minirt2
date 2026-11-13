/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:16:46 by me                #+#    #+#             */
/*   Updated: 2026/11/13 23:21:15 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

t_err	get_amb(char *str, t_scene *sc)
{
	t_parser	p;
	t_err		err;

	p.err = bad_light_config;
	p.required = 2;
	p.addr[0] = &sc->amb.ratio;
	p.addr[1] = &sc->amb.color;
	p.getting_f = get_amb_getter();
	p.passing_f = get_amb_passer();
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	return (ok);
}

t_err	get_light(char *str, t_scene *sc)
{
	t_light		l;
	t_parser	p;
	t_err		err;

	p.err = bad_light_config;
	p.required = 3;
	p.addr[0] = &l.coordinate;
	p.addr[1] = &l.ratio;
	p.addr[2] = &l.color;
	p.getting_f = get_light_getter();
	p.passing_f = get_light_passer();
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	if (!add_light(&sc->light_lst, l))
		return (syscall_err);
	return (ok);
}

t_err	get_cam(char *str, t_scene *sc)
{
	t_parser	p;
	t_err		err;

	p.err = bad_light_config;
	p.required = 3;
	p.addr[0] = &sc->cam.coordinate;
	p.addr[1] = &sc->cam.vec;
	p.addr[2] = &sc->cam.fov;
	p.getting_f = get_cam_getter();
	p.passing_f = get_cam_passer();
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	return (ok);
}
