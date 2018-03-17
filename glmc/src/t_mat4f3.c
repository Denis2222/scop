/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mat4f3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 16:15:43 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 16:15:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glmc.h>

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

t_mat4f	*mat4f_look_at(t_vec3f *eye, t_vec3f *center, t_vec3f *up)
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
	float		tan_half_fovy;
	t_mat4f		*m;

	rad = fov;
	tan_half_fovy = tan(rad / 2.0f);
	m = mat4f();
	m->m[0][0] = 1.0f / (aspect_ratio * tan_half_fovy);
	m->m[1][1] = 1.0f / tan_half_fovy;
	m->m[2][2] = (-1.0f * (near + far)) / (far - near);
	m->m[2][3] = -1.0f;
	m->m[3][2] = (-1.0f * (2 * far * near)) / (far - near);
	return (m);
}
