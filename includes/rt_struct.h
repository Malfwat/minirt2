/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 18:53:51 by me                #+#    #+#             */
/*   Updated: 2026/11/25 21:56:42 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCT_H
# define RT_STRUCT_H

# include <stdbool.h>
# include <sys/time.h>

# include "rt_math.h"
# include "rt_color.h"

typedef int				t_fd;

enum e_obj
{
	sphere,
	cylinder,
	plan,
	cone,
	amb,
	light,
	cam,
	none
};

typedef enum e_obj		t_elem;

typedef struct s_ppm
{
	int			width;
	int			height;
	int			max_value;
	void		*map;
}	t_ppm;

typedef struct s_obj
{
	enum e_obj		id;
	t_coordinate	coordinate;
	t_color			color;
	t_vec3			vec;
	double			diameter;
	double			height;
	double			checker_size;

	double			intensity;
	double			exposant;
	t_ppm			texture;
	struct s_obj	*next;
}	t_obj;

# define NB_COMP 9

typedef struct s_light
{
	t_coordinate	coordinate;
	double			ratio;
	t_color			color;

	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_coordinate	coordinate;
	t_vec3			vec;
	__UINT8_TYPE__	fov;
}	t_cam;

typedef struct s_scene
{
	bool	camera;
	bool	l;
	bool	ambient;

	t_cam	cam;
	t_light	amb;
	t_light	*light_lst;
	t_obj	*obj_lst;
}	t_scene;

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
	t_ppm	*texture;
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

typedef struct timeval	t_time;

typedef struct s_rt
{
	bool		stop;
	t_time		last;
	t_scene		sc;
	t_graphics	data;
}	t_rt;

#endif /*RT_STRUCT_H*/