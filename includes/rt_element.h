/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_element.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:43:09 by me                #+#    #+#             */
/*   Updated: 2026/11/11 17:44:11 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ELEMENT_H
# define RT_ELEMENT_H

# include "rt_struct.h"

void	free_obj(t_obj *lst);
void	free_light(t_light *lst);

#endif /*RT_ELEMENT_H*/