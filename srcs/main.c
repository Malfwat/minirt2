/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:23:24 by me                #+#    #+#             */
/*   Updated: 2026/10/25 15:46:42 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_struct.h"
#include "rt_gnl.h"
#include "rt_error.h"

#include "str.h"

#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	res;

	if (ac != 2)
		return (0);
	if (ft_atoi(av[1], &res))
		printf("%i\n", res);
	else
		printf("NOT AN INTERGER\n");
	return (0);
}
