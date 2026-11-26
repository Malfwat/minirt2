/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ppm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 16:56:47 by me                #+#    #+#             */
/*   Updated: 2026/11/26 23:46:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_parsing.h"
#include "rt_struct.h"
#include "str.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <errno.h>

static t_err	get_map_size(int fd, int *x, int *y)
{
	t_err	err;

	err = get_len(fd, x);
	if (err)
		return (err);
	err = get_len(fd, y);
	if (err)
		return (err);
	return (ok);
}

static t_err	get_max_val(int fd, int *max_size)
{
	return (get_len(fd, max_size));
}

static t_err	get_ppm_id(int fd)
{
	char	c;
	int		bytes_read;

	bytes_read = read(fd, &c, 1);
	if (bytes_read < 0)
		return (syscall_err);
	if (pass_comments(fd, &c) != ok)
		return (syscall_err);
	if (c != 'P')
		return (bad_ppm_config);
	bytes_read = read(fd, &c, 1);
	if (bytes_read < 0)
		return (syscall_err);
	if (c != '6')
		return (bad_ppm_config);
	bytes_read = read(fd, &c, 1);
	if (bytes_read < 0)
		return (syscall_err);
	if (!is_wspace(c))
		return (bad_ppm_config);
	return (ok);
}

static t_err	get_map(int fd, t_ppm *texture)
{
	int		bytes_read;
	int		size;
	void	*map;

	size = texture->width * texture->height * 3;
	map = malloc(sizeof(char) * size);
	if (!map)
		return (close(fd), syscall_err);
	bytes_read = read(fd, map, size);
	if (bytes_read < 0)
		return (free(map), syscall_err);
	if (bytes_read != size)
		return (free(map), bad_ppm_config);
	texture->map = map;
	return (ok);
}

t_err	load_ppm(char const *filename, t_ppm *texture)
{
	int		fd;
	t_err	err;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (bad_ppm_config);
	err = get_ppm_id(fd);
	if (err != ok)
		return (close(fd), err);
	err = get_map_size(fd, &texture->width, &texture->height);
	if (err != ok)
		return (close(fd), err);
	err = get_max_val(fd, &texture->max_value);
	if (err != ok)
		return (free(texture->map), close(fd), err);
	if (texture->max_value > 255)
		return (free(texture->map), close(fd), bad_ppm_config);
	err = get_map(fd, texture);
	if (err != ok)
		return (free(texture->map), close(fd), err);
	close(fd);
	return (ok);
}
