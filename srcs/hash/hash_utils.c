/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 17:09:30 by me                #+#    #+#             */
/*   Updated: 2026/11/26 20:19:08 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "str.h"
#include "rt_error.h"
#include "rt_struct.h"
#include "rt_parsing.h"

long	hash_pathname(unsigned char const *str)
{
	unsigned long	hash;

	hash = HASH_BASE;
	while (*str)
	{
		hash ^= *str;
		hash *= FNV_PRIME;
		str++;
	}
	return (hash % HASH_TABLE_LENGTH);
}

t_err	create_hash_node(char const *str, t_hash **node, t_ppm *tex)
{
	void	*ptr;
	t_hash	*new_node;

	ptr = ft_strdup(str);
	if (!ptr)
		return (syscall_err);
	new_node = malloc(sizeof(t_hash));
	if (!new_node)
		return (free(ptr), syscall_err);
	new_node->pathname = ptr;
	new_node->next = NULL;
	new_node->tex = tex;
	*node = new_node;
	return (ok);
}

t_hash	*get_last_hash_node(t_hash *ptr)
{
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

t_ppm	*get_loaded_ppm(t_hash *lst, char *str)
{
	while (lst)
	{
		if (!ft_strcmp(str, lst->pathname))
			return (lst->tex);
		lst = lst->next;
	}
	return (NULL);
}

t_err	add_hash(t_hash *table[], char *str, t_ppm **ptr)
{
	t_hash	*tmp;
	t_ppm	*tex;
	t_err	err;
	int		index;

	index = hash_pathname((unsigned char const *)str);
	tex = get_loaded_ppm(table[index], str);
	if (tex)
	{
		*ptr = tex;
		return (ok);
	}
	tex = malloc(sizeof(t_ppm));
	if (!tex)
		return (syscall_err);
	err = load_ppm(str, tex);
	if (err != ok)
		return (free(tex), err);
	if (create_hash_node(str, &tmp, tex) != ok)
		return (free(tex), syscall_err);
	tmp->next = table[index];
	table[index] = tmp;
	*ptr = tex;
	return (ok);
}
