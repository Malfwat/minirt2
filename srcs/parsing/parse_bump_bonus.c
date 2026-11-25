/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 21:48:50 by me                #+#    #+#             */
/*   Updated: 2026/11/25 22:13:03 by me               ###   ########.fr       */
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
	t_err	err;
	t_ppm	texture;

	trim_trailling_wspace(str);
	err = load_ppm(str, &texture);
	if (err != ok)
		return (err);
	*(t_ppm *)res = texture;
	return (ok);
}
