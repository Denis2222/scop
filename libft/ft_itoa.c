/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:52:30 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:18:21 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_sign(int n)
{
	if (n >= 0)
		return (0);
	return (1);
}

static int	ft_itoa_length(int n)
{
	int	length;

	length = 1;
	if (ft_itoa_sign(n))
		n = n * -1;
	while (n > 9)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		length;
	int		abs;

	if (n < -2147483647)
		return (ft_strdup("-2147483648"));
	length = ft_itoa_length(n) + ft_itoa_sign(n);
	abs = n;
	if (ft_itoa_sign(n))
		abs = n * -1;
	str = (char*)ft_memalloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	while (length > 0)
	{
		length--;
		str[length] = (abs % 10) + 48;
		abs = abs / 10;
	}
	if (ft_itoa_sign(n))
		str[0] = '-';
	return (str);
}
