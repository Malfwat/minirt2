/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:58:20 by me                #+#    #+#             */
/*   Updated: 2026/11/13 23:14:31 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

t_err	get_sp_comp(char *str, t_obj *o)
{
	t_err			err;
	char			*ptr;
	__UINT8_TYPE__	i;

	i = 0;
	while (i < 3)
	{
		if (!*str)
			return (bad_sp_config);
		ptr = str;
		pass_component(&str);
		if (i == 0)
			err = get_vec3(ptr, &o->coordinate);
		else if (i == 1)
			err = get_diameter(ptr, &o->diameter);
		else
			err = get_color(ptr, &o->color);
		if (err != ok)
			return (err);
		i++;
	}
	if (*str)
		return (bad_sp_config);
	return (ok);
}

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
