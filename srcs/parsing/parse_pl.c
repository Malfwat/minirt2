/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 23:12:52 by me                #+#    #+#             */
/*   Updated: 2026/11/27 02:44:21 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"

t_getter	*get_pl_getter(void)
{
	static t_getter	tab[9] = {
		get_vec3,
		get_vec3,
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

t_pass	*get_pl_passer(void)
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
