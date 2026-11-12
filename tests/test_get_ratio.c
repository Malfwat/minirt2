/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_ratio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:43:32 by me                #+#    #+#             */
/*   Updated: 2026/11/12 12:52:20 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include <stdio.h>

t_err	get_ratio(char *str, double *ratio);

int	main(int ac, char **av)
{
	double res;

	if (ac < 2)
		return (1);
	res = 0;
	while (*++av)
	{
		if (get_ratio(*av, &res) == ok)
			printf("succeed: value: %f\n", res);
		else
			printf("failed\n");
	}
	return (0);
}
