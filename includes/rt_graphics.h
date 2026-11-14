/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 18:35:57 by me                #+#    #+#             */
/*   Updated: 2026/11/14 21:31:36 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GRAPHICS_H
# define RT_GRAPHICS_H

# define ESC 65307

# include "rt_struct.h"

typedef struct s_image
{
	void	*addr;
	void	*img;

	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	t_image	image;
}	t_graphics;

void	put_pxl(int x, int y, t_graphics *data, int color);
void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc);
void	render(t_graphics *data, t_scene *sc);

# define WIDTH 500
# define HEIGHT 500

#endif /*RT_GRAPHICS_H*/