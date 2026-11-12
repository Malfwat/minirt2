/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:57:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/12 20:29:07 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSING_H
# define RT_PARSING_H

# define AMB "A"
# define CAM "C"
# define LIGHT "L"

# define PL "pl"
# define SP "sp"
# define CY "cy"

# include "rt_struct.h"
# include "rt_error.h"

# include <stdbool.h>

void	parse(const char *filename, t_scene *sc);
t_fd	open_scene(const char *filename, t_err *err);
bool	is_line_empty(char *str);
void	null_terminate_component(char *str);
void	pass_id(char **str_ptr);
char	*pass_color_value(char *str, int i);
void	pass_color(char **str_ptr);
void	pass_component(char **str_ptr);

t_err	get_vec3(char *str, t_vec3 *vec);
t_err	get_ratio(char *str, double *ratio);
t_err	get_color(char *str, t_color *color);

t_err	get_amb(char *str, t_scene *sc);
t_err	get_cam(char *str, t_scene *sc);
t_err	get_light(char *str, t_scene *sc);
t_err	get_obj(char *str, t_scene *sc);


typedef	t_err (*parse_functions)(char *, t_scene *);

#endif /* RT_PARSING_H */