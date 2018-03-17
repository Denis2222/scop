/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:30:57 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:05 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int		l;
	char	*cstr;

	cstr = (char*)str;
	l = 0;
	while (*cstr)
	{
		cstr++;
		l++;
	}
	return (l);
}
