/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mat4f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 16:15:11 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:15:20 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

t_mat4f	*mat4f_rotate_x(t_mat4f *m, float angle)
{
	if (m == NULL)
		m = mat4f_identity(1.0f);
	m->m[1][1] = cosf(angle);
	m->m[2][2] = cosf(angle);
	m->m[2][1] = sinf(angle);
	m->m[1][2] = -sinf(angle);
	return (m);
}

t_mat4f	*mat4f_rotate_y(t_mat4f *m, float angle)
{
	if (m == NULL)
		m = mat4f_identity(1.0f);
	m->m[0][0] = cosf(angle);
	m->m[0][2] = sinf(angle);
	m->m[2][0] = -sinf(angle);
	m->m[2][2] = cosf(angle);
	return (m);
}

t_mat4f	*mat4f_rotate_z(t_mat4f *m, float angle)
{
	if (m == NULL)
		m = mat4f_identity(1.0f);
	m->m[0][0] = cosf(angle);
	m->m[0][1] = -sinf(angle);
	m->m[1][0] = sinf(angle);
	m->m[1][1] = cosf(angle);
	return (m);
}

t_mat4f	*mat4f_rotate(t_mat4f *m, float angle, t_vec3f *dir)
{
	t_mat4f	*dst;
	t_mat4f *new;

	new = mat4f_identity(1.0f);
	if (dir->x == 1 && dir->y == 0 && dir->z == 0)
		mat4f_rotate_x(new, angle);
	if (dir->x == 0 && dir->y == 1 && dir->z == 0)
		mat4f_rotate_y(new, angle);
	if (dir->x == 0 && dir->y == 0 && dir->z == 1)
		mat4f_rotate_z(new, angle);
	dst = new;
	if (m != NULL)
	{
		dst = mat4f_multiply(m, new);
		free(new);
	}
	free(m);
	return (dst);
}

t_vec4f	*mat4f_mul_vec4f(t_mat4f *m, t_vec4f *src)
{
	t_vec4f	*dst;

	dst = vec4f(0, 0, 0, 0);
	dst->x =
	m->m[0][0] * src->x +
	m->m[0][1] * src->y +
	m->m[0][2] * src->z +
	m->m[0][3] * src->w;
	dst->y =
	m->m[1][0] * src->x +
	m->m[1][1] * src->y +
	m->m[1][2] * src->z +
	m->m[1][3] * src->w;
	dst->z =
	m->m[2][0] * src->x +
	m->m[2][1] * src->y +
	m->m[2][2] * src->z +
	m->m[2][3] * src->w;
	dst->w =
	m->m[3][0] * src->x +
	m->m[3][1] * src->y +
	m->m[3][2] * src->z +
	m->m[3][3] * src->w;
	return (dst);
}
