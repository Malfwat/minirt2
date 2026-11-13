/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:58:41 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/13 14:40:15 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERROR_H
# define RT_ERROR_H

# define ERRNO -4
# define RT_ERR -2
# define NOT_A_LINE -6

# include "rt_struct.h"

typedef enum e_err
{
	syscall_err = 2,
	ok = 0,
	bad_color_format = -1,
	bad_elem = -2,
	bad_fov_format = -3,
	bad_ratio_format = -4,
	bad_vec_format = -5,
	ext = -6,
	invalid_color_value = -7,
	invalid_double_value = -8,
	invalid_length_value = -9,
	bad_amb_config = -10,
	bad_light_config = -11,
}	t_err;

void	manage_error_and_exit(t_err errnum,
			t_scene *sc, int line);

#endif /* RT_ERROR_H */