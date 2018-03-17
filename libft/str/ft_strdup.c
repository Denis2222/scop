/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:30:35 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:26 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char *str;

	str = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, src);
	return (str);
}
