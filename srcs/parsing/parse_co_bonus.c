/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_co_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:12:52 by me                #+#    #+#             */
/*   Updated: 2026/11/26 20:44:09 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "str.h"

t_getter	*get_co_getter(void)
{
	static t_getter	tab[10] = {
		get_vec3,
		get_vec3,
		get_diameter,
		get_height,
		get_color,
		get_intensity,
		get_exposant,
		get_checker_size,
		get_ppm,
		(void *)0
	};

	return (tab);
}

t_pass	*get_co_passer(void)
{
	static t_pass	tab[10] = {
		pass_component,
		pass_component,
		pass_component,
		pass_component,
		pass_color,
		pass_component,
		pass_component,
		pass_component,
		pass_component,
		(void *)0
	};

	return (tab);
}
