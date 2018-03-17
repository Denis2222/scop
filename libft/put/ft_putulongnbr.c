/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulongnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 05:38:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/03/24 05:38:45 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putulongnbr_fd(unsigned long nbr, int fd)
{
	if (nbr > 9)
	{
		ft_putulongnbr_fd(nbr / 10, fd);
		ft_putulongnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}

void	ft_putulongnbr(unsigned long nbr)
{
	ft_putulongnbr_fd(nbr, 1);
}
