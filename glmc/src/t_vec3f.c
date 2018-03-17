/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:29:58 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:22:56 by dmoureu-         ###   ########.fr       */
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
