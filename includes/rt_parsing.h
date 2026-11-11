/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:57:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/11 17:11:57 by me               ###   ########.fr       */
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

void	parse(const char *filename, t_scene *sc);
int		parse_file(t_fd fd, t_scene *sc, t_err *err, int *line_no);
t_fd	open_scene(const char *filename, t_err *err);

#endif /* RT_PARSING_H */