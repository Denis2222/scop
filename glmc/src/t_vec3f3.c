/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 16:22:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:22:44 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_vec3f	*vec3f_scale(t_vec3f *this, float m)
{
	this->x *= m;
	this->y *= m;
	this->z *= m;
	return (this);
}

t_vec3f	*vec3f_new_scale(t_vec3f *i, float m)
{
	t_vec3f	*v;

	v = vec3f(i->x * m,
			i->y * m,
			i->z * m);
	return (v);
}

void	vec3fedit(t_vec3f *this, float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void	vec3f_cpy(t_vec3f *this, t_vec3f *val)
{
	this->x = val->x;
	this->y = val->y;
	this->z = val->z;
}

void	vec3f_print(t_vec3f *t)
{
	printf("[x:%0.3f, y:%0.3f, z:%0.3f]\n", t->x, t->y, t->z);
}
