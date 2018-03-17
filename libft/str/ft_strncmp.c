/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:31:10 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:40 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, const char *s2, size_t n)
{
	size_t x;

	if (n == 0)
		return (0);
	x = 0;
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0' && x < (n - 1))
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
