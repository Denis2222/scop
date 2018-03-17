/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:37:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:08:59 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_obj	*secure_malloc_obj(void)
{
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	if (obj == NULL)
	{
		printf("Malloc error : exit !\n");
		exit(1);
	}
	return (obj);
}

void	obj_init_color(t_obj *obj_data)
{
	size_t	i;
	t_vec3f	*addr;
	float	color;

	i = 0;
	while (i < obj_data->nvertices)
	{
		if (i % 3 == 0)
			color = (((float)(rand() % 50)) / 100.0f) + 0.1f;
		addr = (t_vec3f*)&obj_data->colors[i * 3];
		vec3fedit(&addr[0], color, color, color);
		i++;
	}
}

void	obj_init(t_obj *obj_data, t_tmp_obj *t)
{
	obj_data->nvertices = list_length(t->vertex_indices);
	obj_data->vertices = (float*)malloc(sizeof(float) * 3 *
		obj_data->nvertices);
	obj_data->nuvs = list_length(t->uv_indices);
	if (obj_data->nuvs > 0)
		obj_data->uvs = (float*)malloc(sizeof(float) * 2 * obj_data->nuvs);
	obj_data->nnormals = list_length(t->normal_indices);
	if (obj_data->nnormals > 0)
		obj_data->normals =
			(float*)malloc(sizeof(float) * 3 * obj_data->nnormals);
	obj_data->tangents = (float*)malloc(sizeof(float) * 3 * obj_data->nnormals);
	obj_data->bitangents =
		(float*)malloc(sizeof(float) * 3 * obj_data->nnormals);
	obj_data->colors = (float*)calloc(3 * obj_data->nvertices, sizeof(float));
	obj_init_color(obj_data);
}
