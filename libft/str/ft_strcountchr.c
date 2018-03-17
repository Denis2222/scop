/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 22:21:43 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:31 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcountchr(char *str, char chr)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			nb++;
		i++;
	}
	return (nb);
}
