/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:26:47 by me                #+#    #+#             */
/*   Updated: 2026/11/14 11:54:19 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "rt_struct.h"
#include "rt_element.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char	**messages(void)
{
	static char	*tab[21] = {
		"Bad color format",
		"Bad element identifier",
		"Bad field of view format",
		"Bad ratio format",
		"Bad vector format",
		"Bad file extension",
		"Color value out of range",
		"Invalid double value",
		"Length must be strictly positive",
		"Bad ambient light configuration",
		"Bad light configuration",
		"Bad camera configuration",
		"Bad sphere configuration",
		"Bad plane configuration",
		"Bad cylinder configuration",
		"Ambient light declared twice",
		"Camera declared twice",
		"Light declared twice",
		"Missing ambient light",
		"Missing light",
		"Missing camera"
	};

	return (tab);
}

char	*err_message(t_err errnum)
{
	if (errnum >= 0 || errnum < -21)
		return ("Unknown error");
	return (messages()[-errnum - 1]);
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
		if (line != NOT_A_LINE)
			printf("Error\n\tMiniRT: line %i: %s\n", line, str);
		else
			printf("Error\n\tMiniRT: %s\n", str);
	}
	free_scene(sc);
	exit(1);
}
