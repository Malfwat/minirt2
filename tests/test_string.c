/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_string.c                                      
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

#include <stdio.h>
#include <stdlib.h>
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

int	main(void)
{
	char	*d;
	char	buf[16];
	int		n;

	check(ft_strlen("") == 0, "strlen vide");
	check(ft_strlen("abc") == 3, "strlen abc");
	check(ft_strchr("abc", 'b') == (char *)"abc" + 1, "strchr trouve");
	check(ft_strchr("abc", 'z') == NULL, "strchr absent");
	check(ft_strchr("70", 0) != NULL, "strchr zero terminal");
	check(ft_strchr_set("70", " ") == NULL, "strchr_set aucun blanc -> NULL");
	check(ft_strchr_set("70 ", " ") != NULL, "strchr_set blanc final -> ptr");
	check(ft_strchr_set("", " ") == NULL, "strchr_set chaine vide -> NULL");
	check(ft_strcmp("abc", "abc") == 0, "strcmp egal");
	check(ft_strcmp("abc", "abd") < 0, "strcmp inferieur");
	check(ft_strncmp("abc", "abd", 2) == 0, "strncmp 2 identiques");
	check(ft_strncmp("abc", "abd", 3) < 0, "strncmp 3 differents");
	d = ft_strdup("hello");
	check(d && !strcmp(d, "hello"), "strdup contenu");
	free(d);
	d = ft_strdup("");
	check(d == NULL, "strdup(\"\") -> NULL (comportement maison, PAS la libc)");
	free(d);
	memset(buf, 'x', sizeof(buf));
	ft_memcpy(buf, "42", 2);
	check(buf[0] == '4' && buf[1] == '2' && buf[2] == 'x', "memcpy 2 octets");
	memset(buf, 'x', sizeof(buf));
	ft_bzero(buf, 4);
	check(buf[0] == 0 && buf[3] == 0 && buf[4] == 'x', "bzero 4 octets");
	check(is_wspace(' ') && is_wspace('\t') && is_wspace('\n'), "wspace sp tab nl");
	check(is_wspace('\r') && is_wspace('\v') && is_wspace('\f'), "wspace cr vt ff");
	check(!is_wspace('a') && !is_wspace(0), "wspace refuse lettre et zero");
	check(is_numeric("123") && !is_numeric("12a"), "is_numeric chiffres et refus lettre");
	check(is_numeric(""), "is_numeric(\"\") -> true (comportement maison)");
	n = 0;
	check(ft_atoi("123", &n) && n == 123, "atoi 123");
	check(ft_atoi("-45", &n) && n == -45, "atoi -45");
	check(ft_atoi("0", &n) && n == 0, "atoi 0");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
