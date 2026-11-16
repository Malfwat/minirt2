/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_errors.c */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"

#include <stdio.h>
#include <string.h>

static int	g_fail;
static int	g_total;

static void	check(int cond, const char *what)
{
	g_total++;
	if (!cond)
	{
		g_fail++;
		printf("FAIL  %s\n", what);
	}
}

char	*err_message(t_err errnum);

int	main(void)
{
	int	code;

	code = -1;
	while (code >= -22)
	{
		check(err_message(code)[0] != 0, "message non vide");
		check(strcmp(err_message(code), "Unknown error") != 0, "message connu");
		code--;
	}
	check(!strcmp(err_message(ok), "Unknown error"), "ok -> Unknown");
	check(!strcmp(err_message(syscall_err), "Unknown error"), "syscall -> Unknown");
	check(!strcmp(err_message(-23), "Unknown error"), "-23 -> Unknown");
	check(!strcmp(err_message(-999), "Unknown error"), "-999 -> Unknown");
	check(!strcmp(err_message(bad_color_format), "Bad color format"), "texte -1");
	check(!strcmp(err_message(ext), "Bad file extension"), "texte -6");
	check(!strcmp(err_message(missing_cam), "Missing camera"), "texte -21");
	check(!strcmp(err_message(vector_null), "Null vector"), "texte -22");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
