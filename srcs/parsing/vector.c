/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:45:31 by me                #+#    #+#             */
/*   Updated: 2026/11/12 21:55:40 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_parsing.h"
#include "rt_error.h"
#include "str.h"

t_err	get_vec3(char *str, void *vec)
{
	char	*ptr;
	t_vec3 	*v;

	v = vec;
	ptr = ft_strchr(str, ',');
	if (!ptr)
		return (bad_vec_format);
	*ptr = 0;
	if (!ft_atof(str, 5, &(v->x)))
		return (invalid_double_value);
	str = ptr + 1;
	ptr = ft_strchr(str, ',');
	if (!ptr)
		return (bad_vec_format);
	*ptr = 0;
	if (!ft_atof(str, 5, &(v->y)))
		return (invalid_double_value);
	str = ptr + 1;
	if (!*str || is_wspace(*str))
		return (bad_vec_format);
	null_terminate_component(str);
	if (!ft_atof(str, 5, &(v->z)))
		return (invalid_double_value);
	return (ok);
}
