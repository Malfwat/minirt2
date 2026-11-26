/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 20:16:14 by me                #+#    #+#             */
/*   Updated: 2026/11/26 20:32:38 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"

#include <stdlib.h>

void	free_hash_lst(t_hash *lst)
{
	void	*ptr;

	while (lst)
	{
		ptr = lst->next;
		free(lst->pathname);
		if (lst->tex)
			free(lst->tex->map);
		free(lst->tex);
		free(lst);
		lst = ptr;
	}
}

void	free_hash_table(t_hash *table[])
{
	int	i;

	i = 0;
	while (i < HASH_TABLE_LENGTH)
		free_hash_lst(table[i++]);
}

t_err	load_link_ppm_to_obj(t_ppm **texture_ptr, t_hash *table[], char *pathname)
{
	t_ppm	*tex;
	t_err	err;

	err = add_hash(table, pathname, &tex);
	if (err)
		return (err);
	*texture_ptr = tex;
	return (ok);
}
