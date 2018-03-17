/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tangent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:58:00 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_vec3f		*ct(t_vec3f *delta_pos1, t_vec3f *delta_pos2,
								t_vec3f *delta_uv1, t_vec3f *delta_uv2)
{
	t_vec3f	*tangent;
	t_vec3f	*delta_pos1t;
	t_vec3f	*delta_pos2t;
	float	r;

	r = 1.0f / (delta_uv1->x * delta_uv2->y - delta_uv1->y * delta_uv2->x);
	delta_pos1t = vec3f(delta_pos1->x, delta_pos1->y, delta_pos1->z);
	delta_pos2t = vec3f(delta_pos2->x, delta_pos2->y, delta_pos2->z);
	vec3f_scale(delta_pos1t, delta_uv2->y);
	vec3f_scale(delta_pos2t, delta_uv1->y);
	tangent = vec3f_scale(vec3f_new_sub(delta_pos1t, delta_pos2t), r);
	free(delta_pos1t);
	free(delta_pos2t);
	return (tangent);
}

t_vec3f		*cb(t_vec3f *delta_pos1, t_vec3f *delta_pos2,
								t_vec3f *delta_uv1, t_vec3f *delta_uv2)
{
	t_vec3f	*bitangent;
	t_vec3f	*delta_pos1b;
	t_vec3f	*delta_pos2b;
	float	r;

	r = 1.0f / (delta_uv1->x * delta_uv2->y - delta_uv1->y * delta_uv2->x);
	delta_pos2b = vec3f(delta_pos2->x, delta_pos2->y, delta_pos2->z);
	delta_pos1b = vec3f(delta_pos1->x, delta_pos1->y, delta_pos1->z);
	vec3f_scale(delta_pos2b, delta_uv1->x);
	vec3f_scale(delta_pos1b, delta_uv2->x);
	bitangent = vec3f_scale(vec3f_new_sub(delta_pos2b, delta_pos1b), r);
	free(delta_pos1b);
	free(delta_pos2b);
	return (bitangent);
}

void		write_tangentinobj(t_obj *o, size_t i, t_vec3f *tangent,
							t_vec3f *bitangent)
{
	vec3f_cpy((t_vec3f*)&o->tangents[(i + 0) * 3], tangent);
	vec3f_cpy((t_vec3f*)&o->tangents[(i + 1) * 3], tangent);
	vec3f_cpy((t_vec3f*)&o->tangents[(i + 2) * 3], tangent);
	vec3f_cpy((t_vec3f*)&o->bitangents[(i + 0) * 3], bitangent);
	vec3f_cpy((t_vec3f*)&o->bitangents[(i + 1) * 3], bitangent);
	vec3f_cpy((t_vec3f*)&o->bitangents[(i + 2) * 3], bitangent);
	free(tangent);
	free(bitangent);
}

void		compute_tangent(t_obj *o)
{
	size_t	i;
	t_vec3f *delta_pos1;
	t_vec3f *delta_pos2;
	t_vec3f *delta_uv1;
	t_vec3f *delta_uv2;

	i = 0;
	while (i < o->nvertices)
	{
		delta_pos1 = vec3f_new_sub((t_vec3f*)&o->vertices[(i + 1) * 3],
			(t_vec3f*)&o->vertices[(i + 0) * 3]);
		delta_pos2 = vec3f_new_sub((t_vec3f*)&o->vertices[(i + 2) * 3],
			(t_vec3f*)&o->vertices[(i + 0) * 3]);
		delta_uv1 = vec3f_new_sub((t_vec3f*)&o->uvs[(i + 1) * 2],
			(t_vec3f*)&o->uvs[(i + 0) * 2]);
		delta_uv2 = vec3f_new_sub((t_vec3f*)&o->uvs[(i + 2) * 2],
			(t_vec3f*)&o->uvs[(i + 0) * 2]);
		write_tangentinobj(o, i, ct(delta_pos1, delta_pos2, delta_uv1,
			delta_uv2), cb(delta_pos1, delta_pos2, delta_uv1, delta_uv2));
		free(delta_pos1);
		free(delta_pos2);
		free(delta_uv1);
		free(delta_uv2);
		i += 3;
	}
}
