/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:36:00 by me                #+#    #+#             */
/*   Updated: 2026/11/12 12:57:34 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "str.h"

t_err	get_ratio(char *str, double *ratio)
{
	char	*ptr;

	ptr = ft_strchr_set(str, "\t\v\n\r\f ");
	if (!ptr)
		ptr = ft_strchr(str, 0);
	else
		*ptr = 0;
	if (ft_strlen(str) > 3)
		return (bad_ratio_format);
	if (!ft_atof(str, 1, ratio))
		return (bad_ratio_format);
	if (*ratio < 0 || *ratio > 1)
		return (bad_ratio_format);
	return (ok);
}
