/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_display.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 18:35:57 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:47:17 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DISPLAY_H
# define RT_DISPLAY_H

# include "rt_error.h"
# include "rt_struct.h"

/**
** @brief convert t_color to an integer a/r/g/b 
** 
** @param[in] c struct s_color
**/
int				t_color_to_int(t_color c);
/**
** @brief Write one pixel into the image buffer
**
** @param[in] x      pixel column
** @param[in] y      pixel row
** @param[in] data   graphics holding the buffer
** @param[in] color  packed colour to write
*/
void			put_pxl(int x, int y, t_graphics *data, int color);
void			render_lines(int y_start, int y_end, t_graphics *data,
					t_scene *sc);
/**
** @brief Render the line designated by one cursor position
**
** @param[in] i  cursor position from 0 to HEIGHT - 1
** @param[in] b  the three bases of the permutation
*/
t_err			render(t_graphics *data, t_scene *sc, int i, int b[]);

/**
 * @brief Return true if the delay between last and now is superior to period
 * 
 * @param[in] n struct timeval now 
 * @param[in] l struct timeval last update
 * @param[in] t period needed before update
 * @return true 
 * @return false 
 */
bool			delayed(t_time n, t_time l, long t);
/**
** @brief MLX loop hook: render one line, refresh on period
**
** @param[in] param  the t_rt of the running program
** @return 0, as MLX expects
*/
int				rendering_loop(void *param);
/**
** @brief Cross hook: end the MLX loop
**
** @param[in] param  the graphics of the closed window
** @return 0, as MLX expects
*/
int				stop_loop(void *param);
/**
** @brief Free the image, the window and the display
**
** @param[in] data  graphics to destroy
*/
void			destroy_graphics(t_graphics *data);
/**
** @brief Key hook: mark the program to stop on escape
**
** @param[in] keycode  key pressed
** @param[in] param    the t_rt of the running program
** @return 0, as MLX expects
*/
int				keyhook(int keycode, void *param);

#endif /*RT_DISPLAY_H*/