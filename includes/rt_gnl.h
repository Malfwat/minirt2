/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:14:46 by me                #+#    #+#             */
/*   Updated: 2026/11/11 18:00:49 by me               ###   ########.fr       */
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

/**
** @brief Read one line from a file descriptor.
**
** @param[in] fd  Descriptor to read, or FREE_GNL to release the stash.
** @return A malloc'd line, its trailing '\n' included, or NULL.
** @retval NULL  End of file (errno untouched), or read/malloc failure
**               (errno set by the failing call). Caller owns the line.
*/
char	*gnl(int fd);
void	free_gnl(t_buf **head);
t_buf	*get_last_node(t_buf *lst);
void	concate(char *buffer, t_buf *head);

# define FREE_GNL -1

#endif /*RT_GNL_H*/