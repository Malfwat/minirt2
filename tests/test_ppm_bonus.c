/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ppm_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 19:05:00 by me                #+#    #+#             */
/*   Updated: 2026/11/25 19:05:00 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Chargeur PPM binaire P6.
**
** Les fichiers de test sont fabriques ici meme, dans un dossier temporaire :
** rien de binaire n'est commite et les cas limites sont explicites.
**
**   tiny.ppm      1x1, en-tete de 11 octets : la longueur de l'en-tete
**                 depend des nombres, un chargeur a offsets fixes le rate
**   comment.ppm   2x1 avec un commentaire '#' dans l'en-tete
**   p3.ppm        PPM ASCII, doit etre refuse
**   short.ppm     en-tete complet mais donnees tronquees
**   absent.ppm    fichier inexistant
**
** Puis la vraie texture assets/textures/earth_atmos_2048.ppm, avec trois
** pixels de reference lus directement dans le fichier.
*/

#include "rt_error.h"
#include "rt_struct.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_err	load_ppm(char const *filename, t_ppm *texture);

static int	g_fail;

static int	ck(const char *label, int cond)
{
	printf("%-56s %s\n", label, cond ? "ok" : "FAIL");
	if (!cond)
		g_fail++;
	return (cond);
}

static void	write_file(char const *path, const char *head,
	const unsigned char *body, int n)
{
	int	fd;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	write(fd, head, strlen(head));
	if (n > 0)
		write(fd, body, n);
	close(fd);
}

static int	pixel(t_ppm *t, int x, int y, int r, int g, int b)
{
	unsigned char	*m;
	int				o;

	m = (unsigned char *)t->map;
	o = (y * t->width + x) * 3;
	if (t->max_value != 255)
		o = (y * t->width + x) * 6;
	return (m[o] == r && m[o + 1] == g && m[o + 2] == b);
}

static void	test_tiny(char const *dir)
{
	char				path[512];
	t_ppm				t;
	const unsigned char	body[3] = {255, 0, 128};

	snprintf(path, sizeof(path), "%s/tiny.ppm", dir);
	write_file(path, "P6\n1 1\n255\n", body, 3);
	memset(&t, 0, sizeof(t));
	ck("1x1 : accepte", load_ppm(path, &t) == ok);
	ck("1x1 : largeur 1, hauteur 1, maxval 255",
		t.width == 1 && t.height == 1 && t.max_value == 255);
	ck("1x1 : le pixel vaut 255,0,128", t.map && pixel(&t, 0, 0, 255, 0, 128));
	free(t.map);
}

static void	test_comment(char const *dir)
{
	char				path[512];
	t_ppm				t;
	const unsigned char	body[6] = {1, 2, 3, 4, 5, 6};

	snprintf(path, sizeof(path), "%s/comment.ppm", dir);
	write_file(path, "P6\n# commentaire dans l'en-tete\n2 1\n255\n", body, 6);
	memset(&t, 0, sizeof(t));
	ck("commentaire : accepte", load_ppm(path, &t) == ok);
	ck("commentaire : largeur 2, hauteur 1", t.width == 2 && t.height == 1);
	ck("commentaire : premier pixel 1,2,3", t.map && pixel(&t, 0, 0, 1, 2, 3));
	ck("commentaire : second pixel 4,5,6", t.map && pixel(&t, 1, 0, 4, 5, 6));
	free(t.map);
}

static void	test_bad(char const *dir)
{
	char				path[512];
	t_ppm				t;
	const unsigned char	body[6] = {1, 2, 3, 4, 5, 6};

	snprintf(path, sizeof(path), "%s/p3.ppm", dir);
	write_file(path, "P3\n1 1\n255\n255 0 0\n", NULL, 0);
	memset(&t, 0, sizeof(t));
	ck("P3 (ASCII) : refuse", load_ppm(path, &t) != ok);
	ck("P3 : la texture reste vide apres echec", t.map == NULL);
	snprintf(path, sizeof(path), "%s/short.ppm", dir);
	write_file(path, "P6\n2 2\n255\n", body, 6);
	memset(&t, 0, sizeof(t));
	ck("donnees tronquees : refuse", load_ppm(path, &t) != ok);
	ck("donnees tronquees : la texture reste vide apres echec", t.map == NULL);
	snprintf(path, sizeof(path), "%s/absent.ppm", dir);
	memset(&t, 0, sizeof(t));
	ck("fichier absent : refuse", load_ppm(path, &t) != ok);
	ck("fichier absent : la texture reste vide apres echec", t.map == NULL);
}

static void	test_earth(void)
{
	t_ppm	t;

	memset(&t, 0, sizeof(t));
	ck("earth_atmos : accepte",
		load_ppm("assets/textures/earth_atmos_2048.ppm", &t) == ok);
	if (!t.map)
		return ;
	ck("earth_atmos : 1024x512, maxval 255",
		t.width == 1024 && t.height == 512 && t.max_value == 255);
	ck("earth_atmos : (0,0) calotte polaire, 255,255,255",
		pixel(&t, 0, 0, 255, 255, 255));
	ck("earth_atmos : (512,256) ocean, 24,36,60",
		pixel(&t, 512, 256, 24, 36, 60));
	ck("earth_atmos : (1023,511) 237,239,240",
		pixel(&t, 1023, 511, 237, 239, 240));
	free(t.map);
}

int	main(void)
{
	char	dir[] = "/tmp/ppm_test.XXXXXX";

	if (!mkdtemp(dir))
	{
		printf("dossier temporaire impossible\n");
		return (1);
	}
	printf("chargeur PPM, fichiers de test dans %s\n\n", dir);
	test_tiny(dir);
	test_comment(dir);
	test_bad(dir);
	test_earth();
	printf("\n%d cas en echec\n", g_fail);
	return (g_fail != 0);
}
