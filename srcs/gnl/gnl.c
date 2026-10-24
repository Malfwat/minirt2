/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:09:54 by me                #+#    #+#             */
/*   Updated: 2026/10/23 21:51:45 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "rt_gnl.h"
#include "str.h"

void	free_gnl(t_buf **head)
{
	t_buf	*lst;
	void	*tmp;

	if (!*head)
		return ;
	lst = *head;
	*head = NULL;
	while (lst)
	{
		tmp = lst;
		free(lst->ptr);
		lst = lst->next;
		free(tmp);
	}
}

t_buf	*get_last_node(t_buf *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

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
	if (bytes_read < 0)
		return (NULL);
	node->ptr[bytes_read] = 0;
	return (node);
}

char	*gnl(int const fd)
{
	static t_buf	*head;

	if (fd < 0)
		return (free_gnl(&head), NULL);
	while (!head || !ft_strchr(get_last_node(head)->ptr, '\n'))
		if (!read_and_put_next(&head, fd))
			return (free_gnl(&head), NULL);
	
	t_buf *tmp = head;
	while (tmp) {
		printf("%s", tmp->ptr);
		tmp = tmp->next;
	}
	free_gnl(&head);
	return (NULL);
}

#include <fcntl.h>

int main(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	gnl(fd);	
	close(fd);
}