/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ppm_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:56:47 by me                #+#    #+#             */
/*   Updated: 2026/11/25 19:08:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"
#include "str.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static t_err	get_map_size(int fd, int *x, int *y, int delta)
{
	t_err	err;

	err = get_len(fd, x, delta);
	if (err)
		return (err);
	err = get_len(fd, y, delta);
	if (err)
		return (err);
	return (ok);
}

static t_err	get_max_val(int fd, int *max_size, int delta)
{
	return (get_len(fd, max_size, delta));
}

static t_err	get_ppm_id(int fd, t_ppm *texture)
{
	char	identifier[3];
	int		bytes_read;

	bytes_read = read(fd, identifier, 3);
	if (bytes_read < 0)
		return (syscall_err);
	if (bytes_read != 3 || !is_wspace(identifier[2]) || identifier[0] != 'P')
		return (bad_ppm_config);
	if (identifier[1] == '6')
		texture->id = p6;
	else if (identifier[1] == '3')
		texture->id = p3;
	else
		return (bad_ppm_config);
	return (ok);
}

static t_err	get_map(int fd, t_ppm *texture)
{
	int		bytes_read;
	int		size;

	size = texture->width * texture->height;
	if (texture->id == p6)
		size *= 4;
	texture->map = malloc(sizeof(char) * size);
	if (!texture->map)
		return (close(fd), syscall_err);
	bytes_read = read(fd, texture->map, size);
	if (bytes_read < 0)
		return (syscall_err);
	if (bytes_read != size)
		return (bad_ppm_config);
	return (ok);
}

t_err	load_ppm(char const *filename, t_ppm *texture)
{
	int		fd;
	int		delta;
	t_err	err;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (syscall_err);
	err = get_ppm_id(fd, texture);
	if (err != ok)
		return (close(fd), err);
	delta = 0;
	if (texture->id == p6)
		delta = '0';
	err = get_map_size(fd, &texture->width, &texture->height, delta);
	if (err != ok)
		return (close(fd), err);
	err = get_max_val(fd, &texture->max_value, delta);
	if (err != ok)
		return (close(fd), err);
	err = get_map(fd, texture);
	if (err != ok)
		return (close(fd), err);
	close(fd);
	return (ok);
}
