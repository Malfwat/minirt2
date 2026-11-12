/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:57:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/12 15:41:37 by me               ###   ########.fr       */
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
void	jump_id(char **str_ptr);
void	null_terminate_component(char *str);

t_err	get_vec3(char *str, t_vec3 *vec);

#endif /* RT_PARSING_H */