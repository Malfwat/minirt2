/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 14:03:21 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/26 20:50:47 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "rt_struct.h"
# define USAGE "Error:\n\t./miniRT<_bonus> scene.rt\n"

void	free_scene(t_scene *sc);
void	manage_error_and_exit(t_err errnum, t_scene *sc, int line);
void	free_hash_table(t_hash *table[]);

#endif /* RT_H */