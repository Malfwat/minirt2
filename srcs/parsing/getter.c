/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:16:46 by me                #+#    #+#             */
/*   Updated: 2026/11/12 21:27:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

t_err	get_amb(char *str, t_scene *sc)
{
	t_err	err;
	char	*ptr;

	ptr	= str;
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

t_err	get_light(char *str, t_scene *sc)
{
	(void)str;
	(void)sc;
	return (ok);
}

t_err	get_obj(char *str, t_scene *sc)
{
	(void)str;
	(void)sc;
	return (ok);
}
