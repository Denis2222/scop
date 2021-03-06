/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec2f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:07:51 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:19:13 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_vec2f	*vec2f(float x, float y)
{
	t_vec2f	*n;

	n = (t_vec2f*)malloc(sizeof(t_vec2f));
	if (!n)
		return (NULL);
	n->x = x;
	n->y = y;
	return (n);
}

t_vec2f	*vec2fedit(t_vec2f *this, float x, float y)
{
	this->x = x;
	this->y = y;
	return (this);
}

void	vec2f_print(t_vec2f *t)
{
	printf("[x:%0.3f, y:%0.3f]\n", t->x, t->y);
}
