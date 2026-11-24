/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:55:21 by me                #+#    #+#             */
/*   Updated: 2026/11/24 12:14:58 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_struct.h"
#include "rt_parsing.h"

t_err	get_strict_positive_double(char *str, double *res)
{
	null_terminate_component(str);
	if (!ft_atof(str, 5, res))
		return (invalid_double_value);
	if (*res <= 0)
		return (invalid_length_value);
	return (ok);
}

t_elem	get_elem(char *line)
{
	if (!ft_strcmp((line), AMB))
		return (amb);
	if (!ft_strcmp((line), CAM))
		return (cam);
	if (!ft_strcmp((line), LIGHT))
		return (light);
	if (!ft_strcmp((line), PL))
		return (plan);
	if (!ft_strcmp((line), CY))
		return (cylinder);
	if (!ft_strcmp((line), SP))
		return (sphere);
	return (none);
}

t_err	get_and_pass_elem(char **str, t_elem *elem)
{
	char	*next;

	next = *str;
	pass_id(&next);
	null_terminate_component(*str);
	*elem = get_elem(*str);
	if (*elem == none)
		return (bad_elem);
	*str = next;
	return (ok);
}

t_parse_functions	get_parsefunc(t_elem elem)
{
	if (elem == amb)
		return (get_amb);
	if (elem == light)
		return (get_light);
	if (elem == cam)
		return (get_cam);
	if (elem == sphere)
		return (get_sp);
	if (elem == cylinder)
		return (get_cy);
	return (get_pl);
}
