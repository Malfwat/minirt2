/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:58:41 by admoufle          #+#    #+#             */
/*   Updated: 2026/10/25 14:55:48 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERROR_H
# define RT_ERROR_H

# define ERRNO -4
# define RT_ERR -2

typedef enum e_err
{
	ext = -1,
	ok
}	t_err;

#endif /* RT_ERROR_H */