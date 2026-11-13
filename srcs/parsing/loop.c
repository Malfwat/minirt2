/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 22:32:39 by me                #+#    #+#             */
/*   Updated: 2026/11/13 22:44:35 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"

t_err	get_comp(char *str, t_parser *p)
{
	t_err			err;
	char			*ptr;
	__UINT8_TYPE__	i;

	i = 0;
	while (p->getting_f[i])
	{
		if (!*str)
			return (p->err);
		ptr = str;
		p->passing_f[i](&str);
		err = p->getting_f[i](ptr, p->addr[i]);
		if (err != ok)
			return (err);
		i++;
	}
	if (*str)
		return (p->err);
	return (ok);
}
