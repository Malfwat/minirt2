/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 15:59:58 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/12 13:11:03 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str.h>
#include <math.h>
#include <stdbool.h>

#include "str.h"

bool	get_decimal(const char *n, double *res, __uint8_t precision)
{
	int	length;

	*res = 0;
	length = ft_strlen(n);
	if (length < precision)
		precision = length;
	while (precision--)
	{
		if (!(n[precision] >= '0' && n[precision] <= '9'))
			return (false);
		*res += n[precision] - '0';
		*res /= 10;
	}
	return (true);
}

bool	get_fixedvalue(const char *n, double *res, __int8_t *sign)
{
	double	prev;

	prev = 0;
	*res = 0;
	*sign = (__int8_t []){1, -1}[*n == '-'];
	if (*n == '-' || *n == '+')
		n++;
	if (!(*n <= '9' && *n >= '0'))
			return (false);
	while (*n && *n != '.')
	{
		if (prev > *res)
			return (false);
		if (!(*n <= '9' && *n >= '0'))
			return (false);
		prev = *res;
		*res = (*res) * 10 + *n - '0';
		n++;
	}
	return (true);
}

bool	ft_atof(const char *n, __uint8_t precision, double *res)
{
	__int8_t	sign;
	double		value;
	double		tmp;
	char		*ptr_dot;

	if (!res || !n || !*n)
		return (false);
	ptr_dot = ft_strchr(n, '.');
	if (ptr_dot && !is_numeric(ptr_dot + 1))
		return (false);
	tmp = 0;
	if ((ptr_dot && (ptr_dot - n) / sizeof(*n) > 40)
		|| (!ptr_dot && ft_strlen(n) > 40)
		|| !get_fixedvalue(n, &value, &sign)
		|| (ptr_dot && !get_decimal(ptr_dot + 1, &tmp, precision)))
		return (false);
	value += tmp;
	*res = value * sign;
	return (true);
}
