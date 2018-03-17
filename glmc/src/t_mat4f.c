/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mat4f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:32:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:39:42 by dmoureu-         ###   ########.fr       */
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

t_mat4f	*mat4f_translate(t_vec3f *t)
{
	t_mat4f *new;

	new = mat4f_identity(1.0f);
	new->m[3][0] = t->x;
	new->m[3][1] = t->y;
	new->m[3][2] = t->z;
	return (new);
}

void	mat4f_print(t_mat4f *m)
{
	int y;

	y = 0;
	printf("_________________________________\n");
	while (y < 4)
	{
		printf("|%10.6f %10.6f %10.6f %10.6f|\n",
		m->m[y][0],
		m->m[y][1],
		m->m[y][2],
		m->m[y][3]);
		y++;
	}
	printf("=================================\n");
	return ;
}

t_mat4f	*mat4f_look_at( t_vec3f *eye, t_vec3f *center, t_vec3f *up)
{
	t_mat4f	*matrix;
	t_vec3f	*f;
	t_vec3f	*s;
	t_vec3f	*u;

	matrix = mat4f_identity(1.0f);
	f = vec3f_norm(vec3f_new_sub(center, eye));
	s = vec3f_norm(vec3f_cross(f, up));
	u = vec3f_cross(s, f);
	matrix->m[0][0] = s->x;
	matrix->m[1][0] = s->y;
	matrix->m[2][0] = s->z;
	matrix->m[0][1] = u->x;
	matrix->m[1][1] = u->y;
	matrix->m[2][1] = u->z;
	matrix->m[0][2] = -f->x;
	matrix->m[1][2] = -f->y;
	matrix->m[2][2] = -f->z;
	matrix->m[3][0] = -vec3f_dot(s, eye);
	matrix->m[3][1] = -vec3f_dot(u, eye);
	matrix->m[3][2] = vec3f_dot(f, eye);
	free(f);
	free(s);
	free(u);
	return (matrix);
}

t_mat4f	*mat4f_perspective(float fov, float aspect_ratio, float near, float far)
{
	float		rad;
	float		tanHalfFovy;
	t_mat4f	*m;

	rad = fov;
	tanHalfFovy = tan(rad / 2.0f);
	m = mat4f();
	m->m[0][0] = 1.0f / (aspect_ratio * tanHalfFovy);
	m->m[1][1] = 1.0f / tanHalfFovy;
	m->m[2][2] = (-1.0f * (near+far)) / (far - near);
	m->m[2][3] = -1.0f;
	m->m[3][2] = (-1.0f * (2 * far * near)) / (far - near);
	return (m);
}

t_mat4f	*mat4f_ortho(float top, float bottom, float left, float right, float near, float far)
{
	t_mat4f *m;

	m = mat4f_identity(1.0f);
	m->m[0][0] = 2.0f / (right - left);
	m->m[1][1] = 2.0f / (top - bottom);
	m->m[2][2] = -2.0f / (far - near);
	m->m[3][0] = -(right + left) / (right - left);
	m->m[3][1] = -(top + bottom) / (top - bottom);
	m->m[3][2] = -(far + near) / (far - near);
	return (m);
}
