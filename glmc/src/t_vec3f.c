/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:29:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:22:52 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_vec3f	*vec3f(float x, float y, float z)
{
	t_vec3f *n;

	n = (t_vec3f*)malloc(sizeof(t_vec3f));
	if (!n)
		return (NULL);
	n->x = x;
	n->y = y;
	n->z = z;
	return (n);
}

float	vec3f_sqrt(t_vec3f *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

float	vec3f_dot(t_vec3f *s, t_vec3f *d)
{
	return (s->x * d->x + s->y * d->y + s->z * d->z);
}

t_vec3f	*vec3f_norm(t_vec3f *v)
{
	float	n;

	n = sqrt(vec3f_sqrt(v));
	v->x /= n;
	v->y /= n;
	v->z /= n;
	return (v);
}

t_vec3f	*vec3f_cross(t_vec3f *s, t_vec3f *d)
{
	float nx;
	float ny;
	float nz;

	nx = s->y * d->z - s->z * d->y;
	ny = s->z * d->x - s->x * d->z;
	nz = s->x * d->y - s->y * d->x;
	return (vec3f(nx, ny, nz));
}

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
