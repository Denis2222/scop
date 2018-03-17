/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glmc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:08:17 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:19:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGLMC_H
# define LIBGLMC_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec3f
{
	float		x;
	float		y;
	float		z;
}				t_vec3f;

typedef struct	s_vec4f
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4f;

typedef struct	s_mat4f
{
	float		m[4][4];
}				t_mat4f;

t_vec2f			*vec2f(float x, float y);
t_vec2f			*vec2fedit(t_vec2f *this, float x, float y);
void			vec2f_print(t_vec2f *t);

t_vec3f			*vec3f(float x, float y, float z);
float			vec3f_sqrt(t_vec3f *v);
float			vec3f_dot(t_vec3f *s, t_vec3f *d);

t_vec3f			*vec3f_sub(t_vec3f *s, t_vec3f *d);
t_vec3f			*vec3f_new_sub(t_vec3f *s, t_vec3f *d);
t_vec3f			*vec3f_norm(t_vec3f *v);
t_vec3f			*vec3f_cross(t_vec3f *s, t_vec3f *d);
t_vec3f			*vec3f_add(t_vec3f *this, t_vec3f *add);
t_vec3f			*vec3f_move(t_vec3f *this, float x, float y, float z);
t_vec3f			*vec3f_new_add(t_vec3f *this, t_vec3f *add);
t_vec3f			*vec3f_scale(t_vec3f *this, float m);
t_vec3f			*vec3f_new_scale(t_vec3f *i, float m);

void			vec3f_cpy(t_vec3f *this, t_vec3f *val);
void			vec3fedit(t_vec3f *this, float x, float y, float z);
void			vec3f_print(t_vec3f *t);

t_vec4f			*vec4f(float x, float y, float z, float w);
float			vec4f_sqrt(t_vec4f *v);
float			vec4f_dot(t_vec4f *s, t_vec4f *d);
t_vec4f			*vec4f_norm(t_vec4f *v);
t_vec4f			*vec4f_cross(t_vec4f *s, t_vec4f *d);
void			vec4f_print(t_vec4f *t);

t_mat4f			*mat4f(void);
t_mat4f			*mat4f_identity(float t);
t_mat4f			*mat4f_multiply(t_mat4f *s, t_mat4f *d);
t_mat4f			*mat4f_translate(t_vec3f *v);

t_mat4f			*mat4f_scale(float x, float y, float z);
t_mat4f			*mat4f_rotate_x(t_mat4f *m, float angle);
t_mat4f			*mat4f_rotate_y(t_mat4f *m, float angle);
t_mat4f			*mat4f_rotate_z(t_mat4f *m, float angle);
t_mat4f			*mat4f_rotate(t_mat4f *m, float angle, t_vec3f *dir);

t_vec4f			*mat4f_mul_vec4f(t_mat4f *m, t_vec4f *src);
t_mat4f			*mat4f_look_at(t_vec3f *eye, t_vec3f *center, t_vec3f *up);
t_mat4f			*mat4f_perspective(float fov, float aspect_ratio, float near,
						float far);
t_mat4f			*mat4f_ortho(float top, float bottom, float left, float right,
						float near, float far);
t_mat4f			*mat4f_init_translation(float x, float y, float z);
t_mat4f			*mat4f_transform_translation(t_mat4f *matrix, t_vec3f *pos);

void			mat4f_print(t_mat4f *m);

#endif
