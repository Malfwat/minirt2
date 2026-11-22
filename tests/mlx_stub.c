/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 23:55:00 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/22 23:55:00 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Remplacement de MiniLibX pour les tests : aucune fenetre, aucun serveur X.
** L'allocation suit les regles de la vraie bibliotheque, pour que les tests
** detectent les doubles frees et les fuites :
**   - mlx_init rend un pointeur alloue, libere par l'appelant apres
**     mlx_destroy_display ;
**   - mlx_new_image alloue l'image ET son buffer, tous deux liberes par
**     mlx_destroy_image.
*/

#include "mlx.h"
#include <stdlib.h>

static int	g_width;
static int	(*g_loop_hook)(void *);
static void	*g_loop_param;

int	g_put_calls;

void	*mlx_init(void)
{
	return (malloc(64));
}

void	*mlx_new_window(void *mlx, int width, int height, char *title)
{
	(void)mlx;
	(void)width;
	(void)height;
	(void)title;
	return (malloc(64));
}

void	*mlx_new_image(void *mlx, int width, int height)
{
	char	**image;

	(void)mlx;
	g_width = width;
	image = malloc(sizeof(*image));
	if (!image)
		return (NULL);
	image[0] = calloc((size_t)width * (size_t)height * 4, 1);
	return (image);
}

char	*mlx_get_data_addr(void *img, int *bits, int *line, int *endian)
{
	*bits = 32;
	*line = g_width * 4;
	*endian = 0;
	return (((char **)img)[0]);
}

int	mlx_hook(void *win, int event, int mask, int (*f)(), void *param)
{
	(void)win;
	(void)event;
	(void)mask;
	(void)f;
	(void)param;
	return (0);
}

int	mlx_key_hook(void *win, int (*f)(), void *param)
{
	(void)win;
	(void)f;
	(void)param;
	return (0);
}

int	mlx_loop_hook(void *mlx, int (*f)(), void *param)
{
	(void)mlx;
	g_loop_hook = f;
	g_loop_param = param;
	return (0);
}

int	mlx_loop(void *mlx)
{
	int	i;

	(void)mlx;
	if (!g_loop_hook)
		return (0);
	i = 0;
	while (i < 2000)
	{
		if (g_loop_hook(g_loop_param))
			break ;
		i++;
	}
	return (0);
}

int	mlx_loop_end(void *mlx)
{
	(void)mlx;
	return (1);
}

int	mlx_put_image_to_window(void *mlx, void *win, void *img, int x, int y)
{
	(void)mlx;
	(void)win;
	(void)img;
	(void)x;
	(void)y;
	g_put_calls++;
	return (0);
}

int	mlx_destroy_image(void *mlx, void *img)
{
	(void)mlx;
	if (!img)
		return (0);
	free(((char **)img)[0]);
	free(img);
	return (0);
}

int	mlx_destroy_window(void *mlx, void *win)
{
	(void)mlx;
	free(win);
	return (0);
}

int	mlx_destroy_display(void *mlx)
{
	(void)mlx;
	return (0);
}
