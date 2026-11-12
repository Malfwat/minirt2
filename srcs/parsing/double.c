/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:13:30 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:43:30 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "str.h"

t_err	get_strict_positive_double(char *str, double *res)
{
	null_terminate_component(str);
	if (!ft_atof(str, 5, res))
		return (invalid_double_value);
	if (*res <= 0)
		return (invalid_length_value);
	return (ok);
}

t_err	get_height(char *str, double *res)
{
	return (get_strict_positive_double(str, res));
}

t_err	get_diameter(char *str, double *res)
{
	return (get_strict_positive_double(str, res));
}
