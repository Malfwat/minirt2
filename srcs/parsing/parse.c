/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:49:24 by me                #+#    #+#             */
/*   Updated: 2026/11/13 16:44:02 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_gnl.h"

#include <unistd.h>
#include <errno.h>

t_err	parse_line(char *str, t_scene *sc)
{
	t_elem	elem;
	t_err	err;

	err = get_and_pass_elem(&str, &elem);
	if (err != ok)
		return (err);
	sc->actual = elem;
	return (get_parsefunc(elem)(str, sc));
}

t_err	parse_file(t_fd fd, t_scene *sc, int *line_no)
{
	char	*line;
	int		i;
	t_err	err;

	line = gnl(fd);
	i = 0;
	while (line)
	{
		*line_no = i;
		if (*line != '#' && !is_line_empty(line))
		{
			err = parse_line(line, sc);
			if (err != ok)
				return (free(line), gnl(FREE_GNL), err);
		}
		free(line);
		line = gnl(fd);
		i++;
	}
	if (errno)
		return (syscall_err);
	return (ok);
}

void	parse(const char *filename, t_scene *sc)
{
	int		line_no;
	t_err	err;
	t_fd	fd;

	err = ok;
	line_no = 0;
	fd = open_scene(filename, &err);
	if (fd < 0)
		return (manage_error_and_exit(syscall_err, sc, NOT_A_LINE));
	err = parse_file(fd, sc, &line_no);
	if (err != ok)
		return (manage_error_and_exit(err, sc, line_no));
	close(fd);
}
