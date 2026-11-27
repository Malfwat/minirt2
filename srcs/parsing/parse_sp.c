/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:12:52 by me                #+#    #+#             */
/*   Updated: 2026/11/27 02:43:55 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"

t_getter	*get_sp_getter(void)
{
	static t_getter	tab[9] = {
		get_vec3,
		get_diameter,
		get_color,
		get_intensity,
		get_exposant,
		get_checker_size,
		get_ppm,
		get_ppm,
		(void *)0
	};

	return (tab);
}

t_pass	*get_sp_passer(void)
{
	static t_pass	tab[9] = {
		pass_component,
		pass_component,
		pass_color,
		pass_component,
		pass_component,
		pass_component,
		pass_component,
		pass_component,
		(void *)0
	};

	return (tab);
}
