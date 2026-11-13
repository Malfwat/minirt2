/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:31:11 by me                #+#    #+#             */
/*   Updated: 2026/11/13 22:49:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_error.h"
#include "str.h"

t_err	get_fov(char *str, void *fov)
{
	int		res;

	null_terminate_component(str);
	if (*str == '+' || !ft_atoi(str, &res))
		return (bad_fov_format);
	if (!(res <= 180 && res >= 0))
		return (bad_fov_format);
	*(__UINT8_TYPE__ *)fov = res;
	return (ok);
}

t_getter	*get_cam_getter(void)
{
	static t_getter	tab[4] = {
		get_vec3,
		get_vec3,
		get_fov,
		NULL
	};

	return (tab);
}

t_pass	*get_cam_passer(void)
{
	static t_pass	tab[4] = {
		pass_component,
		pass_component,
		pass_component,
		NULL
	};

	return (tab);
}
