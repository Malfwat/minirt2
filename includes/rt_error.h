/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:58:41 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/12 14:25:46 by me               ###   ########.fr       */
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
	ext = -10,
	invalid_height_value,
	invalid_diameter_value,
	invalid_color_value,
	invalid_double_value,
	bad_color_format,
	bad_ratio_format,
	bad_fov_format,
	bad_vec_format,
	bad_elem,
	ok
}	t_err;

void	manage_error_and_exit(int err_type, t_err errnum,
			t_scene *sc, int line);

#endif /* RT_ERROR_H */