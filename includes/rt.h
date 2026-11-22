/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:03:21 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/22 03:23:51 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt_struct.h"

void	free_scene(t_scene *sc);

# define USAGE "Error:\n\t./miniRT<_bonus> scene.rt\n"

#endif /* RT_H */