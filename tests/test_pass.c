/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pass.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:44:47 by me                #+#    #+#             */
/*   Updated: 2026/11/12 19:49:09 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	pass_id(char **str_ptr);
void	pass_component(char **str_ptr);
void	pass_color(char **str_ptr);

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	pass_color(&av[1]);
	return (0);
}