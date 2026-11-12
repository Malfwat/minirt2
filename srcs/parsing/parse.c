/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:49:24 by me                #+#    #+#             */
/*   Updated: 2026/11/12 15:08:44 by me               ###   ########.fr       */
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

	if (!ft_strcmp((line), AMB))
		return (amb);
	if (!ft_strcmp((line), CAM))
		return (cam);
	if (!ft_strcmp((line), LIGHT))
		return (light);
	if (!ft_strcmp((line), PL))
		return (plan);
	if (!ft_strcmp((line), CY))
		return (cylinder);
	if (!ft_strcmp((line), SP))
		return (sphere);
	return (none);
}

void	null_terminate_component(char *str)
{
	char	*ptr;

	ptr = ft_strchr_set(str, "\t\v\n\r\f ");
	if (!ptr)
		ptr = ft_strchr(str, 0);
	*ptr = 0;
}

#include <stdio.h>

t_err	parse_line(char *str, t_scene *sc)
{
	t_elem	elem;
	char	*next;

	next = str;
	jump_id(&next);
	null_terminate_component(str);
	elem = get_elem(str);
	if (elem == none)
		return (bad_elem);
	printf("%s", next);
	//jump_id(&str);
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
