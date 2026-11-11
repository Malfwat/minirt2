/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:45:31 by me                #+#    #+#             */
/*   Updated: 2026/11/11 18:59:56 by me               ###   ########.fr       */
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
	ptr = ptr + 1;
	*ptr = 0;
	if (!ft_atof(str, 1, &(vec->x)))
		return (invalid_double_value);
	str = ptr + 1;
	ptr = ft_strchr(str, ',');
	if (!ptr)
		return (bad_vec_format);
	ptr = ptr + 1;
	*ptr = 0;
	if (!ft_atof(str, 1, &(vec->y)))
		return (invalid_double_value);
	ptr = ft_strchr(str, ' ');
	if (!ptr)
		return (bad_vec_format);
	ptr = ptr + 1;
	*ptr = 0;
	if (!ft_atof(str, 1, &(vec->z)))
		return (invalid_double_value);
	return (ok);
}
