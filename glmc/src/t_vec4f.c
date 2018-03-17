/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec4f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:23:13 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:21:37 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_vec4f	*vec4f(float x, float y, float z, float w)
{
	t_vec4f *n;

	n = (t_vec4f*)malloc(sizeof(t_vec4f));
	if (!n)
		return (NULL);
	n->x = x;
	n->y = y;
	n->z = z;
	n->w = w;
	return (n);
}

t_vec4f	*vec4f_norm(t_vec4f *v)
{
	float	n;

	n = sqrt(vec4f_sqrt(v));
	v->x /= n;
	v->y /= n;
	v->z /= n;
	v->w /= n;
	return (v);
}

t_vec4f	*vec4f_cross(t_vec4f *s, t_vec4f *d)
{
	float nx;
	float ny;
	float nz;
	float nw;

	nx = s->y * d->z - s->z * d->y;
	ny = s->z * d->x - s->x * d->z;
	nz = s->x * d->y - s->y * d->x;
	nw = s->w * d->w - s->w * d->w;
	return (vec4f(nx, ny, nz, nw));
}

void	vec4f_print(t_vec4f *t)
{
	printf("[x:%0.1f, y:%0.1f, z:%0.1f, w:%0.1f]\n", t->x, t->y, t->z, t->w);
}
