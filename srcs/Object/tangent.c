/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/14 12:06:25 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_vec3f *compute_tangentt(t_vec3f *deltaPos1, t_vec3f *deltaPos2,
						 t_vec3f *deltaUV1, t_vec3f *deltaUV2)
{
	t_vec3f	*tangent;
	t_vec3f	*deltaPos1t;
	t_vec3f	*deltaPos2t;
	float	r;

	r = 1.0f / (deltaUV1->x * deltaUV2->y - deltaUV1->y * deltaUV2->x);
	deltaPos1t = vec3f(deltaPos1->x, deltaPos1->y, deltaPos1->z);
	deltaPos2t = vec3f(deltaPos2->x, deltaPos2->y, deltaPos2->z);
	vec3f_scale(deltaPos1t, deltaUV2->y);
	vec3f_scale(deltaPos2t, deltaUV1->y);
	tangent = vec3f_scale(vec3f_new_sub(deltaPos1t, deltaPos2t), r);
	free(deltaPos1t);
	free(deltaPos2t);
	return (tangent);
}

t_vec3f *compute_bitangent(t_vec3f *deltaPos1, t_vec3f *deltaPos2,
						 t_vec3f *deltaUV1, t_vec3f *deltaUV2)
{
	t_vec3f	*bitangent;
	t_vec3f	*deltaPos1b;
	t_vec3f	*deltaPos2b;
	float	r;

	r = 1.0f / (deltaUV1->x * deltaUV2->y - deltaUV1->y * deltaUV2->x);
	deltaPos2b = vec3f(deltaPos2->x, deltaPos2->y, deltaPos2->z);
	deltaPos1b = vec3f(deltaPos1->x, deltaPos1->y, deltaPos1->z);
	vec3f_scale(deltaPos2b, deltaUV1->x);
	vec3f_scale(deltaPos1b, deltaUV2->x);
	bitangent = vec3f_scale(vec3f_new_sub(deltaPos2b, deltaPos1b), r);
	free(deltaPos1b);
	free(deltaPos2b);
	return (bitangent);
}


void	write_tangentinobj(t_obj *o, size_t i, t_vec3f *tangent, t_vec3f *bitangent)
{
	vec3f_cpy((t_vec3f*)&o->tangents[ (i + 0) * 3], tangent);
	vec3f_cpy((t_vec3f*)&o->tangents[ (i + 1) * 3], tangent);
	vec3f_cpy((t_vec3f*)&o->tangents[ (i + 2) * 3], tangent);

	vec3f_cpy((t_vec3f*)&o->bitangents[ (i + 0) * 3], bitangent);
	vec3f_cpy((t_vec3f*)&o->bitangents[ (i + 1) * 3], bitangent);
	vec3f_cpy((t_vec3f*)&o->bitangents[ (i + 2) * 3], bitangent);

	free(tangent);
	free(bitangent);
}

void 	compute_tangent(t_obj *o)
{
	size_t	i;
	t_vec3f *deltaPos1;
	t_vec3f *deltaPos2;
	t_vec3f *deltaUV1;
	t_vec3f *deltaUV2;

	i = 0;
	while (i < o->nvertices)
	{
		deltaPos1 = vec3f_new_sub((t_vec3f*)&o->vertices[(i + 1) * 3], (t_vec3f*)&o->vertices[(i + 0) * 3]);
		deltaPos2 = vec3f_new_sub((t_vec3f*)&o->vertices[(i + 2) * 3], (t_vec3f*)&o->vertices[(i + 0) * 3]);
		deltaUV1 = vec3f_new_sub((t_vec3f*)&o->uvs[(i + 1) * 2], (t_vec3f*)&o->uvs[(i + 0) * 2]);
		deltaUV2 = vec3f_new_sub((t_vec3f*)&o->uvs[(i + 2) * 2], (t_vec3f*)&o->uvs[(i + 0) * 2]);
		write_tangentinobj(o, i,
			compute_tangentt(deltaPos1, deltaPos2, deltaUV1, deltaUV2),
			compute_bitangent(deltaPos1, deltaPos2, deltaUV1, deltaUV2)
		);
		free(deltaPos1);
		free(deltaPos2);
		free(deltaUV1);
		free(deltaUV2);
		i += 3;
	}
}
