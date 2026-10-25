/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:09:54 by me                #+#    #+#             */
/*   Updated: 2026/10/25 14:55:23 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "rt_gnl.h"
#include "str.h"

void	pop_node(t_buf **head, t_buf *node)
{
	t_buf	*ptr;

	if (*head == node)
		return (free_gnl(head));
	ptr = *head;
	while (ptr->next != node)
		ptr = ptr->next;
	free(node->ptr);
	free(node);
	ptr->next = NULL;
}

int	read_and_put_next(t_buf **head, int const fd)
{
	t_buf	*node;
	ssize_t	bytes_read;

	node = malloc(sizeof(*node));
	if (!node)
		return (-1);
	node->next = NULL;
	if (!*head)
		*head = node;
	else
		get_last_node(*head)->next = node;
	node->ptr = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!node->ptr)
		return (-1);
	bytes_read = read(fd, node->ptr, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	if (!bytes_read)
		return (pop_node(head, node), 0);
	node->ptr[bytes_read] = 0;
	return (1);
}

bool	update_stash(char *ptr, t_buf **head)
{
	void	*stash;

	stash = ft_strdup(ptr + 1);
	if (!stash)
		return (false);
	ptr[1] = 0;
	free((*head)->ptr);
	(*head)->ptr = stash;
	free_gnl(&(*head)->next);
	return (true);
}

char	*concate_and_stash(t_buf **head)
{
	char	*line;
	size_t	nb_node;
	void	*tmp;

	nb_node = 0;
	tmp = *head;
	while (tmp && ++nb_node)
		tmp = ((t_buf *)tmp)->next;
	if (!nb_node)
		return (NULL);
	line = malloc(sizeof(char) * (nb_node * BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	concate(line, *head);
	tmp = ft_strchr(line, '\n');
	if (tmp && ((char *)tmp)[1])
	{
		if (!update_stash(tmp, head))
			return (free(line), NULL);
		return (line);
	}
	return (free_gnl(head), line);
}

char	*gnl(int const fd)
{
	static t_buf	*head;
	int				ret;

	if (fd < 0)
		return (free_gnl(&head), NULL);
	while (!head || !ft_strchr(get_last_node(head)->ptr, '\n'))
	{
		ret = read_and_put_next(&head, fd);
		if (ret < 0)
			return (free_gnl(&head), NULL);
		else if (ret == 0)
			break ;
	}
	return (concate_and_stash(&head));
}
