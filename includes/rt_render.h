/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 21:02:08 by me                #+#    #+#             */
/*   Updated: 2026/11/24 16:36:35 by me               ###   ########.fr       */
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
/**
** @brief Compute the camera frame once per image
**
** @param[in]  sc    scene holding the camera
** @param[out] data  graphics receiving the axes and the fov offsets
*/
void			build_frame(t_graphics *data, t_scene *sc);
/**
** @brief Convert pixel coordinates to a direction in camera space
**
** @param[in] ox    half width offset of the field of view
** @param[in] oy    half height offset of the field of view
** @param[in] posx  pixel column
** @param[in] posy  pixel row
** @return direction in camera space, its z component set to 1
*/
t_vec3			pxl_to_sysvec(double ox, double oy, double posx, double posy);
/**
** @brief Express a camera space vector in world coordinates
**
** @param[in] axes  camera basis
** @param[in] svec  vector expressed in camera space
** @return the same vector in world coordinates
*/
t_vec3			sysvec_to_real_vec(t_axes axes, t_vec3 svec);
/**
** @brief Convert an angle from degrees to radians
**
** @param[in] angle  angle in degrees
*/
double			deg_to_rad(double angle);

t_color			anti_aliasing(t_graphics *data, t_scene *sc, double x,
					double y);
/**
** @brief Average the four quadrant colours of a pixel
**
** @param[in] q  the four quadrant colours
** @return their mean
*/
t_color			quadrant_mean(t_quadrant q);
/**
** @brief Cast one ray at the centre of each quadrant of a pixel
**
** @param[in] x  pixel column
** @param[in] y  pixel row
** @return the four colours of the quadrants
*/
t_quadrant		get_quadrant(t_graphics *data, t_scene *sc, double x, double y);
/**
** @brief Largest colour spread between the four quadrants
**
** @param[in] q  the four quadrant colours
** @return the biggest difference between the min and max channel
*/
double			quadrant_diff(t_quadrant q);
/**
** @brief Solve a * t * t + b * t + c = 0
**
** @param[in]  q   the three coefficients
** @param[out] s1  first root
** @param[out] s2  second root
** @return true when the discriminant is not negative
*/
bool			quad(t_quad q, double *s1, double *s2);

/**
** @brief Map a cursor position to the line it renders
**
** @param[in] cursor  position from 0 to HEIGHT - 1
** @param[in] b2      end of the first and second families
** @param[in] b3      end of the third family
** @param[in] b4      end of the fourth family
** @return the line number, each line reached exactly once
*/
int				ligne(int cursor, int b2, int b3, int b4);
/**
** @brief Compute the three cumulative bases of the line permutation
**
** @param[out] b  array of three bases, derived from HEIGHT
*/
void			fill_bases(int b[]);

/**
** @brief Turn an accumulated double colour back into a t_color
**
** @param[in] c    accumulated colour
** @param[in] div  number of samples that were summed
** @return the colour divided by div
*/
t_color			cdouble_to_c(t_color_double c, double div);
/**
** @brief Add a t_color to a t_color_double accumulator
**
** @param[in] c  accumulator
** @param[in] x  colour to add
** @return the new accumulator
*/
t_color_double	add_color_double(t_color_double c, t_color x);
/**
** @brief Multiply a colour by a light colour and an intensity
**
** @param[in] a       base colour
** @param[in] light   light whose colour is used
** @param[in] factor  intensity applied to the light
** @return the resulting colour
*/
t_color			mult_color_light(t_color a, t_light light, double factor);
/**
** @brief Add two colours, clamping each channel to 255
**
** @param[in] a  first colour
** @param[in] b  second colour
** @return the sum of both colours
*/
t_color			add_color(t_color a, t_color b);
/**
** @brief Shade an intersection: ambient, then every light
**
** @param[in] hit  intersection to shade
** @param[in] sc   scene holding the lights
** @return the final colour of the point
*/
t_color			get_final_color(t_hit hit, t_scene *sc);
/**
** @brief Contribution of one light, shadows included
**
** @param[in] hit  intersection to shade
** @param[in] l    light to apply
** @param[in] sc   scene holding the objects
** @return the light contribution, zero when shadowed
*/
t_color			get_pixel_illumination(t_hit hit, t_light *l, t_scene *sc);
/**
** @brief Colour of the pixel seen through one ray
**
** @param[in] x  pixel column
** @param[in] y  pixel row
** @return the colour of that pixel
*/
t_color			get_pxl_color(t_scene *sc, t_graphics *d, double x, double y);
/**
** @brief Find the nearest object hit by a ray
**
** @param[in]  data  ray origin, direction and distance limit
** @param[out] ptr   nearest intersection found
** @return true when an object is hit before the limit
*/
bool			cast_ray(t_scene *sc, t_cast data, t_hit *ptr);

t_color			checker_color(t_hit hit, t_obj *obj);
t_color			get_final_color(t_hit hit, t_scene *sc);

#endif /*RT_RENDER_H*/