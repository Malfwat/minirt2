/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 21:02:08 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:36:44 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# include "rt_struct.h"
# include "rt_math.h"

/**
** @brief Give a 3D sytem from one t_vec3
		
**
** @param[in] z 3D non null vector used as z axis of the new system
** @return t_axes	Structure of 3 t_vec3 
*/
t_axes			get_system(t_vec3 z);
void			build_frame(t_graphics *data, t_scene *sc);
t_vec3			pxl_to_sysvec(double ox, double oy, double posx, double posy);
t_vec3			sysvec_to_real_vec(t_axes axes, t_vec3 svec);
double			deg_to_rad(double angle);

t_color			anti_aliasing(t_graphics *data, t_scene *sc, double x,
					double y);
t_color			quadrant_mean(t_quadrant q);
t_quadrant		get_quadrant(t_graphics *data, t_scene *sc, double x, double y);
double			quadrant_diff(t_quadrant q);
bool			quad(t_quad q, double *s1, double *s2);

int				ligne(int cursor, int b2, int b3, int b4);
void			fill_bases(int b[]);

t_color			cdouble_to_c(t_color_double c, double div);
t_color_double	add_color_double(t_color_double c, t_color x);
t_color			mult_color_light(t_color a, t_light light, double factor);
t_color			add_color(t_color a, t_color b);
t_color			get_final_color(t_hit hit, t_scene *sc);
t_color			get_pixel_illumination(t_hit hit, t_light *l, t_scene *sc);
t_color			get_pxl_color(t_scene *sc, t_graphics *d, double x, double y);
bool			cast_ray(t_scene *sc, t_cast data, t_hit *ptr);

#endif /*RT_RENDER_H*/