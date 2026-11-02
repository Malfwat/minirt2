/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 15:59:58 by admoufle          #+#    #+#             */
/*   Updated: 2026/11/02 12:39:47 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str.h>
#include <math.h>
#include <stdbool.h>

bool	get_decimal(const char *n, double *res, __uint8_t precision)
{
	int	i;
	int	length;

	i = 0;
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

bool	get_fixedvalue(const char *n, double *res)
{
	double	prev = 0;
	__int8_t	sign;

	*res = 0;
	sign = (__int8_t []){1, -1}[*n == '-'];
	if (*n == '-' || *n == '+')
		n++;
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
	*res *= sign;
	return (true);
}

bool	ft_atof(const char *n, __uint8_t precision, double *res)
{
	double	value;
	double	tmp;
	char	*ptr_dot;

	if (!res)
		return (false);
	ptr_dot = ft_strchr(n, '.');
	tmp = 0;
	if ((ptr_dot && (ptr_dot - n) / sizeof(*n) > 40)
		|| (!ptr_dot && ft_strlen(n) > 40)
		|| !get_fixedvalue(n, &value)
		|| (ptr_dot && !get_decimal(ptr_dot + 1, &tmp, precision)))
		return (false);
	value += tmp;
	*res = value;
	return (true);
}
