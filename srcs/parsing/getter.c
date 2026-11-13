/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:16:46 by me                #+#    #+#             */
/*   Updated: 2026/11/13 22:49:23 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

t_err	get_amb(char *str, t_scene *sc)
{
	t_err	err;
	char	*ptr;

	ptr = str;
	pass_component(&str);
	err = get_ratio(ptr, &sc->amb.ratio);
	if (err != ok)
		return (err);
	if (!*str)
		return (bad_amb_config);
	ptr = str;
	pass_color(&str);
	err = get_color(ptr, &sc->amb.color);
	if (err != ok)
		return (err);
	if (*str)
		return (bad_amb_config);
	return (ok);
}

t_err	get_cam(char *str, t_scene *sc)
{
	void			*tab[3];
	char			*ptr;
	t_err			err;
	__UINT8_TYPE__	i;

	i = 0;
	tab[0] = &sc->cam.coordinate;
	tab[1] = &sc->cam.vec;
	tab[2] = &sc->cam.fov;
	while (i < 3)
	{
		if (!*str)
			return (bad_cam_config);
		ptr = str;
		pass_component(&str);
		if (i < 2)
			err = get_vec3(ptr, tab[i]);
		else
			err = get_fov(ptr, tab[i]);
		if (err != ok)
			return (err);
		i++;
	}
	return ((t_err []){ok, bad_cam_config}[*str != 0]);
}

//t_err	get_light_comp(char *str, t_parser *p)
//{
//	t_err			err;
//	char			*ptr;
//	__UINT8_TYPE__	i;

//	i = 0;
//	while (p->getting_f[i])
//	{
//		if (!*str)
//			return (p->err);
//		ptr = str;
//		p->passing_f[i](&str);
//		err = p->getting_f[i](ptr, p->addr[i]);
//		if (err != ok)
//			return (err);
//		i++;
//	}
//	if (*str)
//		return (p->err);
//	return (ok);
//}

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
