/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:31:11 by me                #+#    #+#             */
/*   Updated: 2026/11/12 13:39:48 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "str.h"

t_err	get_fov(char *str, __UINT8_TYPE__ *fov)
{
	int		res;
	char	*ptr;

	ptr = ft_strchr_set(str, "\t\v\n\r\f ");
	if (!ptr)
		ptr = ft_strchr(str, 0);
	else
		*ptr = 0;
	if (*str == '+' || !ft_atoi(str, &res))
		return (bad_fov_format);
	if (!(res <= 180 && res >= 0))
		return (bad_fov_format);
	*fov = res;
	return (ok);
}
