/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 18:24:59 by me                #+#    #+#             */
/*   Updated: 2026/11/25 18:46:10 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"

#include <unistd.h>

t_err	get_len(int fd, int *ptr, int delta)
{
	char	buf;
	int		byte_read;
	int		tmp;

	tmp = 0;
	byte_read = read(fd, &buf, 1);
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
