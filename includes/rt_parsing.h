/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:57:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/14 12:09:42 by me               ###   ########.fr       */
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

void				set_bool(bool *l, bool *c, bool *a, t_elem elem);
t_err				parse_line(char *str, t_scene *sc);

void				parse(const char *filename, t_scene *sc);
t_err				open_scene(const char *filename, t_fd *fd);
bool				is_line_empty(char *str);
void				null_terminate_component(char *str);
void				pass_id(char **str_ptr);
char				*pass_color_value(char *str, int i);

void				pass_color(char **str_ptr);
void				pass_component(char **str_ptr);
typedef void	(*t_pass)(char **);

t_pass				*get_light_passer(void);
t_pass				*get_amb_passer(void);
t_pass				*get_cam_passer(void);
t_pass				*get_cy_passer(void);
t_pass				*get_pl_passer(void);
t_pass				*get_sp_passer(void);

t_err				get_vec3(char *str, void *vec);
t_err				get_ratio(char *str, void *ratio);
t_err				get_color(char *str, void *color);
t_err				get_fov(char *str, void *fov);
t_err				get_height(char *str, void *res);
t_err				get_diameter(char *str, void *res);
typedef t_err	(*t_getter)(char *, void *);

t_getter			*get_cy_getter(void);
t_getter			*get_pl_getter(void);
t_getter			*get_sp_getter(void);
t_getter			*get_light_getter(void);
t_getter			*get_amb_getter(void);
t_getter			*get_cam_getter(void);
bool				add_light(t_light **head, t_light data);

t_err				get_amb(char *str, t_scene *sc);
t_err				get_cam(char *str, t_scene *sc);
t_err				get_light(char *str, t_scene *sc);
t_err				get_cy(char *str, t_scene *sc);
t_err				get_pl(char *str, t_scene *sc);
t_err				get_sp(char *str, t_scene *sc);
//t_err	get_obj(char *str, t_scene *sc);
//t_err	get_obj(char *str, t_scene *sc);

t_err				add_obj(t_scene *sc, t_obj o);

typedef t_err	(*t_parse_functions)(char *, t_scene *);

t_err				get_and_pass_elem(char **str, t_elem *elem);
t_parse_functions	get_parsefunc(t_elem elem);

typedef struct s_parser
{
	t_getter		*getting_f;
	t_pass			*passing_f;

	t_err			err;
	__UINT8_TYPE__	required;
	void			*addr[NB_COMP + 1];
}	t_parser;

t_err				get_comp(char *str, t_parser *p);

#endif /* RT_PARSING_H */