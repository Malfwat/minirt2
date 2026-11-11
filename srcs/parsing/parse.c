/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:49:24 by me                #+#    #+#             */
/*   Updated: 2026/11/11 17:15:41 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "rt_error.h"
#include "rt_parsing.h"

#include <unistd.h>

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
