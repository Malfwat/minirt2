/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:14:46 by me                #+#    #+#             */
/*   Updated: 2026/10/25 14:36:16 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GNL_H
# define RT_GNL_H

# define BUFFER_SIZE 511

# include <stdlib.h>

typedef struct s_buf
{
	char			*ptr;
	struct s_buf	*next;
}	t_buf;

char	*gnl(int fd);
void	free_gnl(t_buf **head);
t_buf	*get_last_node(t_buf *lst);
void	concate(char *buffer, t_buf *head);

#endif /*RT_GNL_H*/