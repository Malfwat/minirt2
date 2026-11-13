/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:58:20 by me                #+#    #+#             */
/*   Updated: 2026/11/13 23:41:08 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

t_err	get_sp(char *str, t_scene *sc)
{
	t_err		err;
	t_parser	p;
	t_obj		o;

	ft_bzero(&o, sizeof(t_obj));
	p.required = 3;
	p.err = bad_sp_config;
	p.addr[0] = &o.coordinate;
	p.addr[1] = &o.diameter;
	p.addr[2] = &o.color;
	p.getting_f = get_sp_getter();
	p.passing_f = get_sp_passer();
	o.id = sphere;
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	return (add_obj(sc, o));
}

t_err	get_pl(char *str, t_scene *sc)
{
	t_err		err;
	t_parser	p;
	t_obj		o;

	ft_bzero(&o, sizeof(t_obj));
	p.required = 3;
	p.err = bad_pl_config;
	p.addr[0] = &o.coordinate;
	p.addr[1] = &o.vec;
	p.addr[2] = &o.color;
	p.getting_f = get_pl_getter();
	p.passing_f = get_pl_passer();
	o.id = plan;
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	return (add_obj(sc, o));
}

t_err	get_cy(char *str, t_scene *sc)
{
	t_err		err;
	t_parser	p;
	t_obj		o;

	ft_bzero(&o, sizeof(t_obj));
	p.required = 5;
	p.err = bad_cy_config;
	p.addr[0] = &o.coordinate;
	p.addr[1] = &o.vec;
	p.addr[2] = &o.diameter;
	p.addr[3] = &o.height;
	p.addr[4] = &o.color;
	p.getting_f = get_cy_getter();
	p.passing_f = get_cy_passer();
	o.id = cylinder;
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	return (add_obj(sc, o));
}
