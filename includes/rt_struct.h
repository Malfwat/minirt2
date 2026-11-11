/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 18:53:51 by me                #+#    #+#             */
/*   Updated: 2026/11/11 18:40:23 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCT_H
# define RT_STRUCT_H

# include <stddef.h>

typedef int			t_fd;

enum e_obj
{
	sphere,
	cylinder,
	plan,
	amb,
	light,
	cam,
	none
};

typedef enum e_obj	t_elem;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3		t_coordinate;

typedef struct s_color
{
	__UINT8_TYPE__	r;
	__UINT8_TYPE__	g;
	__UINT8_TYPE__	b;
}	t_color;

typedef struct s_obj
{
	enum e_obj		id;
	t_coordinate	coordinate;
	t_color			color;
	t_vec3			vec;
	double			diameter;
	double			height;

	struct s_obj	*next;
}	t_obj;

typedef struct s_ambient
{
	t_color			color;
	t_coordinate	coordinate;
	double			ratio;
}	t_amb;

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
	t_cam	cam;
	t_amb	amb;
	t_light	*light_lst;
	t_obj	*obj_lst;
}	t_scene;

#endif /*RT_STRUCT_H*/