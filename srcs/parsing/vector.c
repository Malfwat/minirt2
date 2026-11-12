/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:45:31 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:26:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "str.h"

t_err	get_vec3(char *str, t_vec3 *vec)
{
	char	*ptr;

	ptr = ft_strchr(str, ',');
	if (!ptr)
		return (bad_vec_format);
	*ptr = 0;
	if (!ft_atof(str, 5, &(vec->x)))
		return (invalid_double_value);
	str = ptr + 1;
	ptr = ft_strchr(str, ',');
	if (!ptr)
		return (bad_vec_format);
	*ptr = 0;
	if (!ft_atof(str, 5, &(vec->y)))
		return (invalid_double_value);
	str = ptr + 1;
	if (!*str || is_wspace(*str))
		return (bad_vec_format);
	ptr = ft_strchr_set(str, "\t\v\n\r\f ");
	if (!ptr)
		ptr = ft_strchr(str, 0);
	*ptr = 0;
	if (!ft_atof(str, 5, &(vec->z)))
		return (invalid_double_value);
	return (ok);
}
