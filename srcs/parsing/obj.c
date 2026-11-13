/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 17:58:20 by me                #+#    #+#             */
/*   Updated: 2026/11/13 18:04:52 by me               ###   ########.fr       */
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
	t_err			err;
	t_obj			o;

	ft_bzero(&o, sizeof(t_obj));
	o.id = sphere;
	err = get_sp_comp(str, &o);
	if (err != ok)
		return (err);
	return (add_obj(sc, o));
}
