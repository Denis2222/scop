/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 16:23:09 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:23:15 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_vec3f	*vec3f_add(t_vec3f *this, t_vec3f *add)
{
	this->x += add->x;
	this->y += add->y;
	this->z += add->z;
	return (this);
}

t_vec3f	*vec3f_move(t_vec3f *this, float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
	return (this);
}

t_vec3f	*vec3f_new_add(t_vec3f *this, t_vec3f *add)
{
	t_vec3f	*new;

	new = vec3f(this->x + add->x,
				this->y + add->y,
				this->z + add->z);
	return (new);
}

t_vec3f	*vec3f_sub(t_vec3f *this, t_vec3f *add)
{
	this->x -= add->x;
	this->y -= add->y;
	this->z -= add->z;
	return (this);
}

t_vec3f	*vec3f_new_sub(t_vec3f *s, t_vec3f *d)
{
	t_vec3f *forward;

	forward = vec3f(s->x - d->x, s->y - d->y, s->z - d->z);
	return (forward);
}
