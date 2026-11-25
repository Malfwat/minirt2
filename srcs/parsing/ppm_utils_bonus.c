/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 18:24:59 by me                #+#    #+#             */
/*   Updated: 2026/11/25 18:28:05 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_error.h"

#include <unistd.h>

t_err	get_len(int fd, int *ptr)
{
	char	buf[3];
	int		byte_read;
	int		tmp;

	ft_bzero(buf, 3 * sizeof(char));
	tmp = 0;
	byte_read = read(fd, buf, 3);
	while (byte_read == 3 && !is_wspace(buf[1]))
	{
		tmp *= 10;
		tmp += buf[1] - '0';
		byte_read = read(fd, buf, 3);
	}
	if (byte_read < 0)
		return (syscall_err);
	if (byte_read != 3)
		return (bad_ppm_config);
	*ptr = tmp;
	return (ok);
}
