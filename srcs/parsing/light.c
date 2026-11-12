/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:36:00 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:44:23 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "str.h"

t_err	get_ratio(char *str, double *ratio)
{
	null_terminate_component(str);
	if (!ft_atof(str, 4, ratio))
		return (bad_ratio_format);
	if (*ratio < 0 || *ratio > 1)
		return (bad_ratio_format);
	return (ok);
}
