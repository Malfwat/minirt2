/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 01:52:52 by me                #+#    #+#             */
/*   Updated: 2026/11/22 03:50:12 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_graphics_bonus.h"

#include <semaphore.h>
#include <stdbool.h>

void	sem_n_post(sem_t *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_post(s + i);
		i++;
	}
}

void	sem_n_wait(sem_t *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_wait(s + i);
		i++;
	}
}

void	close_sem_tab(sem_t tab[], int n)
{
	int	i;

	i = 0;
	while (i < n)
		sem_destroy(tab + i++);
}

bool	init_sem_tab(sem_t	tab[])
{
	int	i;

	i = 0;
	while (i < NB_TH)
	{
		if (sem_init(tab + i, 0, 1))
			return (close_sem_tab(tab, i), false);
		i++;
	}
	return (true);
}
