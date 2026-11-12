/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:13:30 by me                #+#    #+#             */
/*   Updated: 2026/11/12 14:17:28 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "str.h"

t_err	get_double(char *str, double *res)
{
	char	*ptr;

	ptr = ft_strchr_set(str, "\t\v\n\r\f ");
	if (!ptr)
		ptr = ft_strchr(str, 0);
	*ptr = 0;
	if (!ft_atof(str, 5, res))
		return (invalid_double_value);
	return (ok);
}

t_err	get_height(char *str, double *res)
{
	return (get_double(str, res));
}


t_err	get_diameter(char *str, double *res)
{
	return (get_double(str, res));
}
