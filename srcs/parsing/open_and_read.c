/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:55:10 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/11 17:13:24 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_gnl.h"
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

t_fd	open_scene(const char *filename, t_err *err)
{
	t_fd	fd;

	if (!is_rt(filename))
	{
		*err = ext;
		return (RT_ERR);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERRNO);
	return (fd);
}

t_err	parse_line(char *str, t_scene *sc)
{
	(void)str;
	(void)sc;
	return (ok);
}

int	parse_file(t_fd fd, t_scene *sc, t_err *err, int *line_no)
{
	char	*line;
	int		i;

	line = gnl(fd);
	i = 0;
	while (line)
	{
		if (*line != '#')
		{
			*err = parse_line(line, sc);
			if (*err != ok)
				return (gnl(FREE_GNL), RT_ERR);
		}
		free(line);
		line = gnl(fd);
		i++;
	}
	if (errno)
		return (ERRNO);
	*line_no = i;
	return (ok);
}
