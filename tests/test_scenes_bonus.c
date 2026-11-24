/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scenes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 00:20:00 by me                #+#    #+#             */
/*   Updated: 2026/11/25 00:20:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Garde-fou : chaque scene de scenes/valid et scenes/bonus doit s'ouvrir.
**
** parse() sort du programme par manage_error_and_exit des qu'une ligne est
** refusee, donc chaque scene est parsee dans un processus fils : un plantage
** ou un exit devient un echec local au lieu d'arreter la batterie.
**
** Le fils renvoie le nombre d'objets et de lumieres comptes dans la liste, et
** le pere compare au nombre de lignes sp/pl/cy/co et L du fichier. Une scene
** qui perd des objets ou qui en invente est donc signalee.
*/

#include "rt_error.h"
#include "rt_struct.h"
#include "rt_element.h"
#include "rt_parsing.h"
#include "rt.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_counts
{
	int	objs;
	int	lights;
}	t_counts;

static int	g_fail;

static int	starts_with(const char *line, const char *tag)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (!strncmp(line, tag, strlen(tag))
		&& (line[strlen(tag)] == ' ' || line[strlen(tag)] == '\t'));
}

static t_counts	count_in_file(const char *path)
{
	t_counts	c;
	char		buf[4096];
	FILE		*f;
	char		*line;

	c.objs = 0;
	c.lights = 0;
	f = fopen(path, "r");
	if (!f)
		return (c);
	line = fgets(buf, sizeof(buf), f);
	while (line)
	{
		if (starts_with(line, "sp") || starts_with(line, "pl")
			|| starts_with(line, "cy") || starts_with(line, "co"))
			c.objs++;
		if (starts_with(line, "L"))
			c.lights++;
		line = fgets(buf, sizeof(buf), f);
	}
	fclose(f);
	return (c);
}

static int	count_list(t_obj *o)
{
	int	n;

	n = 0;
	while (o)
	{
		n++;
		o = o->next;
	}
	return (n);
}

static int	count_lights(t_light *l)
{
	int	n;

	n = 0;
	while (l)
	{
		n++;
		l = l->next;
	}
	return (n);
}

static int	parse_in_child(const char *path, t_counts *out)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	t_scene	sc;
	t_counts	c;

	if (pipe(fd) < 0)
		return (-1);
	fflush(stdout);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		memset(&sc, 0, sizeof(sc));
		parse(path, &sc);
		c.objs = count_list(sc.obj_lst);
		c.lights = count_lights(sc.light_lst);
		free_scene(&sc);
		if (write(fd[1], &c, sizeof(c)) != (ssize_t)sizeof(c))
			_exit(2);
		close(fd[1]);
		_exit(0);
	}
	close(fd[1]);
	fflush(stdout);
	if (read(fd[0], out, sizeof(*out)) != (ssize_t)sizeof(*out))
	{
		out->objs = -1;
		out->lights = -1;
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && out->objs >= 0)
		return (0);
	out->objs = -1;
	out->lights = -1;
	return (-1);
}

static void	check_scene(const char *dir, const char *name)
{
	char		path[512];
	t_counts	got;
	t_counts	want;
	int			bad;

	snprintf(path, sizeof(path), "%s/%s", dir, name);
	want = count_in_file(path);
	bad = (parse_in_child(path, &got) != 0);
	if (!bad && (got.objs != want.objs || got.lights != want.lights))
		bad = 1;
	printf("%-46s %-4s objets %d/%d  lumieres %d/%d\n", path,
		bad ? "FAIL" : "ok", got.objs, want.objs, got.lights, want.lights);
	if (bad)
		g_fail++;
}

static int	run_dir(const char *dir)
{
	DIR				*d;
	struct dirent	*e;
	char			path[512];
	int				n;

	d = opendir(dir);
	if (!d)
	{
		printf("%-46s %-4s repertoire absent\n", dir, "FAIL");
		g_fail++;
		return (0);
	}
	n = 0;
	e = readdir(d);
	while (e)
	{
		if (e->d_name[0] != '.'
			&& strlen(e->d_name) > 3
			&& !strcmp(e->d_name + strlen(e->d_name) - 3, ".rt"))
		{
			snprintf(path, sizeof(path), "%s/%s", dir, e->d_name);
			check_scene(dir, e->d_name);
			n++;
		}
		e = readdir(d);
	}
	closedir(d);
	return (n);
}

int	main(void)
{
	int	total;

	total = run_dir("scenes/valid");
	total += run_dir("scenes/bonus");
	printf("\n%d scene(s), %d en echec\n", total, g_fail);
	if (total == 0)
	{
		printf("aucune scene trouvee : lancer depuis la racine du depot\n");
		return (1);
	}
	return (g_fail != 0);
}
