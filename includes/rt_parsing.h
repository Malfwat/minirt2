/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:57:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/27 02:45:18 by me               ###   ########.fr       */
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
# define CO "co"

# define SPECULAR 2
# define CHECKER 1
# define BUMP 1
# define NORM 1

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
t_err				load_ppm(char const *filename, t_ppm *texture);
t_err				add_hash(t_hash *table[], char *str, t_ppm **ptr);
t_err				load_link_ppm_to_obj(t_ppm **texture_ptr,
						t_hash *table[], char *pathname);

void				pass_color(char **str_ptr);
void				pass_component(char **str_ptr);
typedef void	(*t_pass)(char **);

t_pass				*get_light_passer(void);
t_pass				*get_amb_passer(void);
t_pass				*get_cam_passer(void);
t_pass				*get_co_passer(void);
t_pass				*get_cy_passer(void);
t_pass				*get_pl_passer(void);
t_pass				*get_sp_passer(void);

t_err				get_vec3(char *str, void *vec);
t_err				get_ratio(char *str, void *ratio);
t_err				get_color(char *str, void *color);
t_err				get_fov(char *str, void *fov);
t_err				get_strict_positive_double(char *str, double *res);
t_err				get_height(char *str, void *res);
t_err				get_diameter(char *str, void *res);
t_err				get_exposant(char *str, void *res);
t_err				get_intensity(char *str, void *res);
t_err				get_checker_size(char *str, void *res);
t_err				get_ppm(char *str, void *res);
typedef t_err	(*t_getter)(char *, void *);

t_getter			*get_co_getter(void);
t_getter			*get_cy_getter(void);
t_getter			*get_pl_getter(void);
t_getter			*get_sp_getter(void);
t_getter			*get_light_getter(void);
t_getter			*get_amb_getter(void);
t_getter			*get_cam_getter(void);
bool				add_light(t_light **head, t_light data);

t_elem				get_elem(char *line);
t_err				get_amb(char *str, t_scene *sc);
t_err				get_cam(char *str, t_scene *sc);
t_err				get_light(char *str, t_scene *sc);
t_err				get_co(char *str, t_scene *sc);
t_err				get_cy(char *str, t_scene *sc);
t_err				get_pl(char *str, t_scene *sc);
t_err				get_sp(char *str, t_scene *sc);

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

t_err				load_ppm(char const *filename, t_ppm *texture);
t_err				get_len(int fd, int *ptr);
t_err				pass_comments(int fd, char *ptr);
t_err				pass_wspace(int fd, char *ptr);

#endif /* RT_PARSING_H */