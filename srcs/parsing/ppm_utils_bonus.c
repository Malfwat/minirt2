/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 18:24:59 by me                #+#    #+#             */
/*   Updated: 2026/11/25 20:57:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"

#include <unistd.h>

t_err	pass_wspace(int fd, char *ptr)
{
	int		byte_read;
	char	c;

	c = *ptr;
	while (is_wspace(c))
	{
		byte_read = read(fd, &c, 1);
		if (byte_read < 0)
			return (syscall_err);
		if (!byte_read)
			return (bad_ppm_config);
	}
	*ptr = c;
	return (ok);
}

static t_err	pass_comment(int fd)
{
	int		byte_read;
	char	c;

	byte_read = read(fd, &c, 1);
	while (byte_read == 1)
	{
		if (c == '\n')
			return (ok);
		byte_read = read(fd, &c, 1);
	}
	if (byte_read < 0)
		return (syscall_err);
	return (ok);
}

t_err	pass_comments(int fd, char *ptr)
{
	int		bytes_read;
	char	c;

	c = *ptr;
	while (c == '#')
	{
		if (pass_comment(fd) != ok)
			return (syscall_err);
		bytes_read = read(fd, &c, 1);
		if (bytes_read < 0)
		return (syscall_err);
		pass_wspace(fd, ptr);
	}
	*ptr = c;
	return (ok);
}

t_err	get_len(int fd, int *ptr)
{
	char	buf;
	int		byte_read;
	int		tmp;

	tmp = 0;
	byte_read = read(fd, &buf, 1);
	while (buf == '#' || is_wspace(buf))
	{
		if (buf == '#' && pass_comments(fd, &buf) != ok)
			return (syscall_err);
		pass_wspace(fd, &buf);
	}
	while (byte_read > 0 && !is_wspace(buf))
	{
		tmp *= 10;
		tmp += buf - '0';
		byte_read = read(fd, &buf, 1);
	}
	if (byte_read < 0)
		return (syscall_err);
	*ptr = tmp;
	return (ok);
}
