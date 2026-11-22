/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:03:21 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/22 20:44:38 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt_struct.h"
# define USAGE "Error:\n\t./miniRT<_bonus> scene.rt\n"

void	free_scene(t_scene *sc);
void	manage_error_and_exit(t_err errnum, t_scene *sc, int line);

#endif /* RT_H */