/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 18:35:57 by me                #+#    #+#             */
/*   Updated: 2026/11/18 18:27:55 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GRAPHICS_H
# define RT_GRAPHICS_H

# define ESC 65307
# define W_CROSS 17

# include "rt_struct.h"
# include "rt_error.h"

typedef struct s_image
{
	void	*addr;
	void	*img;

	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_axes
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;
}	t_axes;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	t_axes	axes;
	t_image	image;
}	t_graphics;

void	put_pxl(int x, int y, t_graphics *data, int color);
void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc);
t_err	render(t_graphics *data, t_scene *sc);
int		t_color_to_int(t_color c);

/** 
** @brief Give a 3D sytem from one t_vec3
**
** @param[in] z 3D non null vector used as z axis of the new system
** @return t_axes	Structure of 3 t_vec3 
*/
t_axes	get_system(t_vec3 z);

double	deg_to_rad(double angle);

# define WIDTH 900
# define HEIGHT 600

# ifndef NB_TH
#  define NB_TH 8
# endif /*NB_TH*/

#endif /*RT_GRAPHICS_H*/