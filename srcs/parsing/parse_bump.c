/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 21:48:50 by me                #+#    #+#             */
/*   Updated: 2026/11/27 03:31:59 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"
#include "str.h"

void	trim_trailling_wspace(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (str[--len])
	{
		if (!is_wspace(str[len]))
			break ;
		str[len] = 0;
	}
}

t_err	get_ppm(char *str, void *res)
{
	t_err		err;
	t_parse_ppm	*data;
	t_ppm		*texture;

	null_terminate_component(str);
	trim_trailling_wspace(str);
	data = res;
	err = load_link_ppm_to_obj(&texture, data->table, str);
	if (err != ok)
		return (err);
	*data->tex = texture;
	return (ok);
}
