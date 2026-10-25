/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 15:04:42 by admoufle          #+#    #+#             */
/*   Updated: 2026/10/25 15:46:51 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_limits.h"
#include "str.h"

bool	is_numeric(const char *n)
{
	while (*n)
	{
		if (*n > '9' || *n < '0')
			return (false);
		n++;
	}
	return (true);
}

bool	is_integer(const char *n)
{
	int	i;
	int	len;

	i = 0;
	if (*n == '-' || *n == '+')
		i++;
	if (!*n)
		return (false);
	while (n[i] && n[i] == '0')
		i++;
	if (!is_numeric(n + i))
		return (false);
	len = ft_strlen(n + i);
	if (len < INT_LENGTH)
		return (true);
	else if (len > INT_LENGTH)
		return (false);
	if (*n == '-')
		return (ft_strcmp(n + i, STR_INT_MIN + 1) <= 0);
	return (ft_strcmp(n + i, STR_INT_MAX) <= 0);
}

bool	ft_atoi(const char *n, int *res)
{
	int	value;
	int	i;

	if (!is_integer(n))
		return (false);
	i = (int []){0, 1}[*n == '+' || *n == '-'];
	value = 0;
	while (n[i])
	{
		value *= 10;
		value += n[i] - '0';
		i++;
	}
	*res = value * (int []){-1, 1}[*n != '-'];
	return (true);
}
