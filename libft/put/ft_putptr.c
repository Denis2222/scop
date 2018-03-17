/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 20:15:32 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/23 21:09:53 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_itoa_hex_min(int nb)
{
	if (nb >= 0 && nb <= 9)
		return ('0' + nb);
	else
		return ('a' + nb - 10);
}

void		ft_putptr(void *ptr)
{
	size_t	nb;
	char	str[20];
	int		i;

	i = 18;
	nb = (size_t)ptr;
	while (nb >= 1)
	{
		str[i] = ft_itoa_hex_min(nb % 16);
		nb = nb / 16;
		i--;
	}
	write(1, "0x", 2);
	write(1, &str[i + 1], 18 - i);
}
