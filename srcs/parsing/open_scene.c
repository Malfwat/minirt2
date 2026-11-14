/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:55:10 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/14 12:06:57 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_struct.h"
#include "rt_error.h"

#include <fcntl.h>
#include <errno.h>

bool	is_rt(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 3, ".rt"))
		return (false);
	return (true);
}

/* Voir comment je veux gerer mes erreurs, si j'utilise errno 
ou si j'implemente ma gestion personelle.
Je peux aussi avoir les deux selon le type d'erreur.
Si c'est systeme, errno si c'est metier mon enum */

t_err	open_scene(const char *filename, t_fd *fd)
{
	if (!is_rt(filename))
		return (ext);
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (syscall_err);
	return (ok);
}
