/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:03:21 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/13 14:52:38 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt_struct.h"
# include "rt_error.h"

t_fd	open_scene(const char *filename, t_err *err);
t_err	parse_line(char *str, t_scene *sc);
void	free_scene(t_scene *sc);

#endif /* RT_H */