/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:26:47 by me                #+#    #+#             */
/*   Updated: 2026/11/13 14:47:15 by me               ###   ########.fr       */
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

void	manage_error_and_exit(t_err errnum, t_scene *sc, int line)
{
	char	*str;

	if (errnum == syscall_err)
	{
		str = strerror(errno);
		printf("Error\n\tMiniRT: %s\n", str);
	}
	else
	{
		str = err_message(errnum);
		printf("Error\n\tMiniRT: line %i: %s\n", line, str);
	}
	free_scene(sc);
	exit(1);
}
