/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gnl.c */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 16:00:00 by me                #+#    #+#             */
/*   Updated: 2026/11/16 16:00:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gnl.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

static int	make_file(const char *path, const char *content)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	write(fd, content, strlen(content));
	close(fd);
	return (open(path, O_RDONLY));
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = make_file("/tmp/gnl_test.txt", "A 0.2\nB\nC");
	check(fd >= 0, "ouverture fichier de test");
	line = gnl(fd);
	check(line && !strcmp(line, "A 0.2\n"), "1re ligne garde le \\n");
	free(line);
	line = gnl(fd);
	check(line && !strcmp(line, "B\n"), "2e ligne");
	free(line);
	line = gnl(fd);
	check(line && !strcmp(line, "C"), "derniere ligne sans \\n");
	free(line);
	errno = 0;
	line = gnl(fd);
	check(line == NULL && errno == 0, "EOF: NULL et errno inchange");
	gnl(FREE_GNL);
	close(fd);
	fd = make_file("/tmp/gnl_empty.txt", "");
	line = gnl(fd);
	check(line == NULL, "fichier vide -> NULL");
	errno = 0;
	line = gnl(-42);
	check(line == NULL, "fd negatif: traite comme FREE_GNL, renvoie NULL");
	gnl(FREE_GNL);
	close(fd);
	fd = make_file("/tmp/gnl_reset.txt", "X\nY\n");
	line = gnl(fd);
	free(line);
	gnl(FREE_GNL);
	line = gnl(fd);
	check(line == NULL, "FREE_GNL jette le buffer deja lu (fd deja consomme)");
	free(line);
	gnl(FREE_GNL);
	close(fd);
	unlink("/tmp/gnl_test.txt");
	unlink("/tmp/gnl_empty.txt");
	unlink("/tmp/gnl_reset.txt");
	printf("\n%d cas en echec sur %d\n", g_fail, g_total);
	return (g_fail != 0);
}
