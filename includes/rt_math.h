/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 22:17:34 by me                #+#    #+#             */
/*   Updated: 2026/11/18 22:27:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATH_H
# define RT_MATH_H

# include "rt_struct.h"

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
}	t_quad;

t_vec3	add(t_vec3 a, t_vec3 b);
t_vec3	cross(t_vec3 a, t_vec3 b);
t_vec3	mult(t_vec3 a, double scal);
t_vec3	sub(t_vec3 a, t_vec3 b);
t_vec3	normalize(t_vec3 vec);
double	get_norme(t_vec3 vec);
double	scal(t_vec3 a, t_vec3 b);
bool	solve_hit(t_quad q, double *t);

#endif /*RT_MATH_H*/