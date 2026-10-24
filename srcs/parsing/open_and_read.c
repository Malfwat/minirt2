/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:55:10 by admoufle          #+#    #+#             */
/*   Updated: 2026/10/24 17:00:35 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gnl.h"
#include "rt_struct.h"
#include "rt_error.h"

t_fd    open_scene(const char *filename, t_err *err)
{
    if (!is_rt(filename))
    {
        *err = ext;
        return (-1);
    }
}