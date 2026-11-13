/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:36:00 by me                #+#    #+#             */
/*   Updated: 2026/11/13 21:37:47 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "str.h"

t_err	get_ratio(char *str, void *ratio)
{
	double	*r;

	r = ratio;
	null_terminate_component(str);
	if (!ft_atof(str, 4, r))
		return (bad_ratio_format);
	if (*r < 0 || *r > 1)
		return (bad_ratio_format);
	return (ok);
}

t_getter	*get_light_getter(void)
{
	static t_getter	tab[4] = {
		get_vec3,
		get_ratio,
		get_color,
		NULL
	};

	return (tab);
}

t_pass	*get_light_passer(void)
{
	static t_pass	tab[4] = {
		pass_component,
		pass_component,
		pass_color,
		NULL
	};

	return (tab);
}

t_getter	*get_amb_getter(void)
{
	static t_getter	tab[3] = {
		get_ratio,
		get_color,
		NULL
	};

	return (tab);
}

t_pass	*get_amb_passer(void)
{
	static t_pass	tab[3] = {
		pass_component,
		pass_color,
		NULL
	};

	return (tab);
}
