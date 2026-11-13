/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:16:46 by me                #+#    #+#             */
/*   Updated: 2026/11/13 14:54:37 by me               ###   ########.fr       */
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
	(void)str;
	(void)sc;
	return (ok);
}

t_err	get_light_comp(char *str, void **ptrs, getter *fptr)
{
	t_err			err;
	char			*ptr;
	__UINT8_TYPE__	i;

	i = 0;
	while (i < 3)
	{
		if (!*str)
			return (bad_light_config);
		ptr = str;
		pass_component(&str);
		err = fptr[i](ptr, ptrs[i]);
		if (err != ok)
			return (err);
		i++;
	}
	return (ok);
}

t_err	get_light(char *str, t_scene *sc)
{
	t_light	l;
	t_err	err;
	void	*l_comp_addr[3];

	l_comp_addr[0] = &l.coordinate;
	l_comp_addr[1] = &l.ratio;
	l_comp_addr[2] = &l.color;
	err = get_light_comp(str, l_comp_addr, get_light_getter());
	if (err != ok)
		return (err);
	if (!add_light(&sc->light_lst, l))
		return (syscall_err);
	return (ok);
}

t_err	get_obj(char *str, t_scene *sc)
{
	(void)str;
	(void)sc;
	return (ok);
}
