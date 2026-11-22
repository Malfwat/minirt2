/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_display.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 18:35:57 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:35:23 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DISPLAY_H
# define RT_DISPLAY_H

# include "rt_error.h"
# include "rt_struct.h"

/**
 * @brief convert t_color to an integer a/r/g/b 
 * 
 * @param c struct s_color
 * @return ** int 
 */
int				t_color_to_int(t_color c);
void			put_pxl(int x, int y, t_graphics *data, int color);
void			render_lines(int y_start, int y_end, t_graphics *data,
					t_scene *sc);
t_err			render(t_graphics *data, t_scene *sc, int i, int b[]);

/**
 * @brief Return true if the delay between last and now is superior to period
 * 
 * @param n struct timeval now 
 * @param l struct timeval last update
 * @param t period needed before update
 * @return true 
 * @return false 
 */
bool			delayed(t_time n, t_time l, long t);
int				rendering_loop(void *param);
int				stop_loop(void *param);
void			destroy_graphics(t_graphics *data);
int				keyhook(int keycode, void *param);

#endif /*RT_DISPLAY_H*/