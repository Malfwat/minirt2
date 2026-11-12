/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:49:11 by me                #+#    #+#             */
/*   Updated: 2026/11/12 17:35:39 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "rt_parsing.h"

void	pass_elem(char **str_ptr)
{
	char	*ptr;

	ptr = *str_ptr;
	ptr = ft_strchr_set(ptr, " \t\v\r\f");
	if (!ptr)
		ptr = ft_strchr(*str_ptr, 0);
	while (*ptr && ft_strchr("\t\v\r\f ", *ptr))
		ptr++;
	*str_ptr = ptr;
}

void	pass_id(char **str_ptr)
{
	return (pass_elem(str_ptr));
}

void	pass_component(char **str_ptr)
{
	return (pass_elem(str_ptr));
}

void	pass_color(char **str_ptr)
{
	__UINT8_TYPE__	i;
	char			*tmp;

	i = 0;
	while (i < 2)
	{
		*str_ptr = ft_strchr(*str_ptr, ',');
		(*str_ptr)++;
		i++;
	}
	if (**str_ptr == ' ')
		(*str_ptr)++;
	tmp = ft_strchr_set(*str_ptr, "\t\v\n\r\f ");
	if (!tmp)
		tmp = ft_strchr(*str_ptr, 0);
	while (*tmp && is_wspace(*tmp))
		tmp++;
	*str_ptr = tmp;
}
