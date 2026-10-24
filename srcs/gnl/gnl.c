/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:09:54 by me                #+#    #+#             */
/*   Updated: 2026/10/24 16:53:00 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "rt_gnl.h"
#include "str.h"

t_buf	*read_and_put_next(t_buf **head, int const fd)
{
	t_buf	*node;
	ssize_t	bytes_read;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->next = NULL;
	if (!*head)
		*head = node;
	else
		get_last_node(*head)->next = node;
	node->ptr = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!node->ptr)
		return (NULL);
	bytes_read = read(fd, node->ptr, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	node->ptr[bytes_read] = 0;
	return (node);
}

void	concate(char *buffer, t_buf *head)
{
	size_t	len;

	while (head)
	{
		len = ft_strlen(head->ptr);
		ft_memcpy(buffer, head->ptr, len);
		head = head->next;
		buffer += len;
	}
	*buffer = 0;
}

char	*concate_and_stash(t_buf **head)
{
	char	*line;
	size_t	nb_node;
	void	*tmp;
	void	*stash;

	nb_node = 0;
	tmp = *head;
	while (tmp && ++nb_node)
		tmp = ((t_buf *)tmp)->next;
	line = malloc(sizeof(char) * (nb_node * BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	concate(line, *head);
	tmp = ft_strchr(line, '\n');
	if (tmp && ((char *)tmp)[1])
	{
		stash = ft_strdup(tmp + 1);
		if (!stash)
			return (free(line), NULL);
		((char *)tmp)[1] = 0;
		free((*head)->ptr);
		(*head)->ptr = stash;
		return (free_gnl(&(*head)->next), line);
	}
	return (free_gnl(head), line);
}

char	*gnl(int const fd)
{
	static t_buf	*head;

	if (fd < 0)
		return (free_gnl(&head), NULL);
	while (!head || !ft_strchr(get_last_node(head)->ptr, '\n'))
		if (!read_and_put_next(&head, fd))
			return (free_gnl(&head), NULL);
	return (concate_and_stash(&head));
}
