/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:57:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/13 17:46:19 by me               ###   ########.fr       */
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

t_err	get_vec3(char *str, void *vec);
t_err	get_ratio(char *str, void *ratio);
t_err	get_color(char *str, void *color);
t_err	get_fov(char *str, __UINT8_TYPE__ *fov);
t_err	get_height(char *str, double *res);
t_err	get_diameter(char *str, double *res);
typedef	t_err (*getter)(char *, void *);

getter	*get_light_getter(void);
bool	add_light(t_light **head, t_light data);

t_err	get_amb(char *str, t_scene *sc);
t_err	get_cam(char *str, t_scene *sc);
t_err	get_light(char *str, t_scene *sc);
t_err	get_sp(char *str, t_scene *sc);
//t_err	get_obj(char *str, t_scene *sc);
//t_err	get_obj(char *str, t_scene *sc);

t_err	add_obj(t_scene *sc, t_obj o);

typedef	t_err (*parse_functions)(char *, t_scene *);

t_err	get_and_pass_elem(char **str, t_elem *elem);
parse_functions	get_parsefunc(t_elem elem);

#endif /* RT_PARSING_H */