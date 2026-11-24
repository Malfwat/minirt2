/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 23:56:34 by me                #+#    #+#             */
/*   Updated: 2026/11/24 23:57:49 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_element.h"

t_intersect	get_intersect_f(enum e_obj id)
{
	if (id == sphere)
		return (sp_hit);
	if (id == plan)
		return (pl_hit);
	if (id == cylinder)
		return (cy_hit);
	return ((t_intersect)0);
}
