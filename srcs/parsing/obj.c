/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:58:20 by me                #+#    #+#             */
/*   Updated: 2026/11/27 02:51:07 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"
#include "rt_math.h"
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
	p.addr[3] = &o.intensity;
	p.addr[4] = &o.exposant;
	p.addr[5] = &o.checker_size;
	sc->tex = (t_parse_ppm){&o.texture, sc->table};
	p.addr[6] = &sc->tex;
	sc->norm = (t_parse_ppm){&o.normals, sc->table};
	p.addr[7] = &sc->norm;
	p.getting_f = get_sp_getter();
	p.passing_f = get_sp_passer();
	o.id = sphere;
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	return (add_obj(sc, o));
}

static t_parser	attrib_pl_pars(t_obj *o, t_scene *sc)
{
	t_parser	p;

	p.required = 3;
	p.err = bad_pl_config;
	p.addr[0] = &o->coordinate;
	p.addr[1] = &o->vec;
	p.addr[2] = &o->color;
	p.addr[3] = &o->intensity;
	p.addr[4] = &o->exposant;
	p.addr[5] = &o->checker_size;
	sc->tex = (t_parse_ppm){&o->texture, sc->table};
	p.addr[6] = &sc->tex;
	sc->norm = (t_parse_ppm){&o->normals, sc->table};
	p.addr[7] = &sc->norm;
	p.getting_f = get_pl_getter();
	p.passing_f = get_pl_passer();
	return (p);
}

t_err	get_pl(char *str, t_scene *sc)
{
	t_err		err;
	t_parser	p;
	t_obj		o;

	ft_bzero(&o, sizeof(t_obj));
	p = attrib_pl_pars(&o, sc);
	o.id = plan;
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	if (get_norme(o.vec) < 1e-04)
		return (vector_null);
	o.vec = normalize(o.vec);
	return (add_obj(sc, o));
}

static t_parser	attrib_cy_pars(t_obj *o, t_scene *sc)
{
	t_parser	p;

	p.required = 5;
	p.err = bad_cy_config;
	p.addr[0] = &o->coordinate;
	p.addr[1] = &o->vec;
	p.addr[2] = &o->diameter;
	p.addr[3] = &o->height;
	p.addr[4] = &o->color;
	p.addr[5] = &o->intensity;
	p.addr[6] = &o->exposant;
	p.addr[7] = &o->checker_size;
	sc->tex = (t_parse_ppm){&o->texture, sc->table};
	p.addr[8] = &sc->tex;
	sc->norm = (t_parse_ppm){&o->normals, sc->table};
	p.addr[9] = &sc->norm;
	p.getting_f = get_cy_getter();
	p.passing_f = get_cy_passer();
	return (p);
}

t_err	get_cy(char *str, t_scene *sc)
{
	t_err		err;
	t_parser	p;
	t_obj		o;

	ft_bzero(&o, sizeof(t_obj));
	p = attrib_cy_pars(&o, sc);
	o.id = cylinder;
	err = get_comp(str, &p);
	if (err != ok)
		return (err);
	if (get_norme(o.vec) < 1e-04)
		return (vector_null);
	o.vec = normalize(o.vec);
	return (add_obj(sc, o));
}
