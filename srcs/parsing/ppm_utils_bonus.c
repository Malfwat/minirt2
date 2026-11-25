/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 18:24:59 by me                #+#    #+#             */
/*   Updated: 2026/11/25 19:57:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"

#include <unistd.h>

static t_err	pass_comment(int fd)
{
	int		byte_read;
	char	c;

	byte_read = read(fd, &c, 1);
	while (byte_read == 1)
	{
		if (is_wspace(c))
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
	}
	*ptr = c;
	return (ok);
}

t_err	get_len(int fd, int *ptr, int delta)
{
	char	buf;
	int		byte_read;
	int		tmp;

	tmp = 0;
	byte_read = read(fd, &buf, 1);
	if (buf == '#' && pass_comments(fd, &buf) != ok)
		return (syscall_err);
	printf("%c----", buf);
	while (byte_read > 0 && !is_wspace(buf))
	{
		tmp *= 10;
		tmp += buf - delta;
		byte_read = read(fd, &buf, 1);
	}
	if (byte_read < 0)
		return (syscall_err);
	*ptr = tmp;
	return (ok);
}
