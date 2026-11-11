/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:26:47 by me                #+#    #+#             */
/*   Updated: 2026/11/11 17:15:26 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_struct.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*err_message(t_err errnum)
{
	if (errnum == ext)
		return ("Invalid file extension");
	return ("");
}

void	free_scene(t_scene *sc)
{
	(void)sc;
}

void	manage_error_and_exit(int err_type, t_err errnum, t_scene *sc, int line)
{
	char	*str;

	if (err_type == ERRNO)
		str = strerror(errno);
	else
		str = err_message(errnum);
	if (line < 0)
		printf("MiniRT: %s\n", str);
	else
		printf("MiniRT: line %i: %s\n", line, str);
	free_scene(sc);
	exit(1);
}
