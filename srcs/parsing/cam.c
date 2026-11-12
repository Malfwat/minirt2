/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:31:11 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:43:45 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parsing.h"
#include "rt_error.h"
#include "str.h"

t_err	get_fov(char *str, __UINT8_TYPE__ *fov)
{
	int		res;

	null_terminate_component(str);
	if (*str == '+' || !ft_atoi(str, &res))
		return (bad_fov_format);
	if (!(res <= 180 && res >= 0))
		return (bad_fov_format);
	*fov = res;
	return (ok);
}
