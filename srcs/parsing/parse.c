/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:49:24 by me                #+#    #+#             */
/*   Updated: 2026/11/11 19:00:46 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_gnl.h"
#include "str.h"

#include <unistd.h>
#include <errno.h>

t_elem	get_elem(char *line)
{
	if (!ft_strncmp((line), AMB, 2))
		return (amb);
	if (!ft_strncmp((line), CAM, 2))
		return (cam);
	if (!ft_strncmp((line), LIGHT, 2))
		return (light);
	if (!ft_strncmp((line), PL, 3))
		return (plan);
	if (!ft_strncmp((line), CY, 3))
		return (cylinder);
	if (!ft_strncmp((line), SP, 3))
		return (sphere);
	return (none);
}

t_err	parse_line(char *str, t_scene *sc)
{
	t_elem	elem;

	elem = get_elem(str);
	if (elem == none)
		return (bad_elem);
	(void)sc;
	return (ok);
}

bool	is_line_empty(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (false);
		str++;
	}
	return (true);
}

int	parse_file(t_fd fd, t_scene *sc, t_err *err, int *line_no)
{
	char	*line;
	int		i;

	line = gnl(fd);
	i = 0;
	while (line)
	{
		*line_no = i;
		if (*line != '#' && !is_line_empty(line))
		{
			*err = parse_line(line, sc);
			if (*err != ok)
				return (free(line), gnl(FREE_GNL), RT_ERR);
		}
		free(line);
		line = gnl(fd);
		i++;
	}
	if (errno)
		return (ERRNO);
	return (ok);
}

void	parse(const char *filename, t_scene *sc)
{
	int		line_no;
	int		err_type;
	t_err	err;
	t_fd	fd;

	err = ok;
	line_no = 0;
	fd = open_scene(filename, &err);
	if (fd < 0)
		return (manage_error_and_exit(fd, err, sc, NOT_A_LINE));
	err_type = parse_file(fd, sc, &err, &line_no);
	if (err_type != ok)
		return (manage_error_and_exit(fd, err, sc, line_no));
	close(fd);
}
