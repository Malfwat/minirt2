/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 21:24:53 by me                #+#    #+#             */
/*   Updated: 2026/11/22 21:29:15 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COLOR_H
# define RT_COLOR_H

typedef struct s_color
{
	__UINT8_TYPE__	r;
	__UINT8_TYPE__	g;
	__UINT8_TYPE__	b;
}	t_color;

typedef struct s_quadrant
{
	t_color	colors[4];
}	t_quadrant;

typedef struct s_color_double
{
	double	r;
	double	g;
	double	b;
}	t_color_double;

#endif /*RT_COLOR_H*/