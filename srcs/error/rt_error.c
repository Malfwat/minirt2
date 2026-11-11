/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:26:47 by me                #+#    #+#             */
/*   Updated: 2026/11/11 18:37:42 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_struct.h"
#include "rt_element.h"

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
	free_light(sc->light_lst);
	free_obj(sc->obj_lst);
}

void	manage_error_and_exit(int err_type, t_err errnum, t_scene *sc, int line)
{
	char	*str;

	if (err_type == ERRNO)
		str = strerror(errno);
	else
		str = err_message(errnum);
	if (line < 0)
		printf("Error\n\tMiniRT: %s\n", str);
	else
		printf("Error\n\tMiniRT: line %i: %s\n", line, str);
	free_scene(sc);
	exit(1);
}
