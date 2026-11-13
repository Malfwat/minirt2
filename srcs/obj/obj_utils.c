/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/13 18:05:21 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "str.h"

#include <stdlib.h>

void	free_obj(t_obj *lst)
{
	void	*ptr;

	while (lst)
	{
		ptr = lst;
		lst = lst->next;
		free(ptr);
	}
}

t_err	add_obj(t_scene *sc, t_obj o)
{
	t_obj	*node;

	node = malloc(sizeof(t_obj));
	if (!node)
		return (syscall_err);
	ft_memcpy(node, &o, sizeof(t_obj));
	node->next = sc->obj_lst;
	sc->obj_lst = node;
	return (ok);
}
