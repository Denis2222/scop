/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mat4f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:32:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:15:35 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_mat4f	*mat4f(void)
{
	t_mat4f	*m;
	int		x;
	int		y;

	m = NULL;
	m = (t_mat4f*)malloc(sizeof(float) * 16);
	if (!m)
		return (NULL);
	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			m->m[x][y] = 0;
			y++;
		}
		x++;
	}
	return (m);
}

t_mat4f	*mat4f_identity(float t)
{
	t_mat4f *m;

	m = mat4f();
	m->m[0][0] = t;
	m->m[1][1] = t;
	m->m[2][2] = t;
	m->m[3][3] = 1.0f;
	return (m);
}

t_mat4f	*mat4f_scale(float x, float y, float z)
{
	t_mat4f *scale;

	scale = mat4f_identity(1.0f);
	scale->m[0][0] = x;
	scale->m[1][1] = y;
	scale->m[2][2] = z;
	return (scale);
}

t_mat4f	*mat4f_multiply(t_mat4f *s, t_mat4f *d)
{
	t_mat4f	*new;
	int		x;
	int		y;

	new = mat4f();
	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			new->m[x][y] = (s->m[x][0] * d->m[0][y]) +
						(s->m[x][1] * d->m[1][y]) +
						(s->m[x][2] * d->m[2][y]) +
						(s->m[x][3] * d->m[3][y]);
			y++;
		}
		x++;
	}
	return (new);
}

t_mat4f	*mat4f_translate(t_vec3f *t)
{
	t_mat4f *new;

	new = mat4f_identity(1.0f);
	new->m[3][0] = t->x;
	new->m[3][1] = t->y;
	new->m[3][2] = t->z;
	return (new);
}
