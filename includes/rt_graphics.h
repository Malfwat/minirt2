/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_graphics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 18:35:57 by me                #+#    #+#             */
/*   Updated: 2026/11/20 00:03:08 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GRAPHICS_H
# define RT_GRAPHICS_H

# define ESC 65307
# define W_CROSS 17

# include "rt_error.h"
# include "rt_math.h"
# include "rt_struct.h"

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
	double	ox;
	double	oy;
	t_axes	axes;
	t_image	image;
}	t_graphics;

typedef struct s_hit_data
{
	t_obj	*obj;
	double	t;
	t_vec3	p;
	t_vec3	normal;
}	t_hit;

typedef struct s_raycast
{
	t_vec3	dir;
	t_vec3	origin;
	double	lim;
}	t_cast;

typedef struct s_pxl_color_data
{
	double	dif;
	double	spec;

	t_color	c_dif;
	t_color	c_spec;
}	t_pxl_data;

typedef struct s_quadrant
{
	t_color	colors[4];
}	t_quadrant;

void	put_pxl(int x, int y, t_graphics *data, int color);
void	render_lines(int y_start, int y_end, t_graphics *data, t_scene *sc);
t_err	render(t_graphics *data, t_scene *sc);
int		t_color_to_int(t_color c);
t_color	mult_color_light(t_color a, t_light light, double factor);
t_color	add_color(t_color a, t_color b);
t_color	get_final_color(t_hit hit, t_scene *sc);
t_color	get_pixel_illumination(t_hit hit, t_light *l, t_scene *sc);
bool	cast_ray(t_scene *sc, t_cast data, t_hit *ptr);
bool	quad(t_quad q, double *s1, double *s2);

/**
** @brief Give a 3D sytem from one t_vec3
		
**
** @param[in] z 3D non null vector used as z axis of the new system
** @return t_axes	Structure of 3 t_vec3 
*/
t_axes	get_system(t_vec3 z);
void	build_frame(t_graphics *data, t_scene *sc);
t_vec3	sysvec_to_real_vec(t_axes axes, t_vec3 svec);
t_vec3	pxl_to_sysvec(double ox, double oy, double posx, double posy);

double	deg_to_rad(double angle);

# define WIDTH 1920
# define HEIGHT 1080

# ifndef NB_TH
#  define NB_TH 8
# endif /*NB_TH*/

#endif /*RT_GRAPHICS_H*/