/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 07:30:08 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void add_mesh(t_obj *obj, const char *path)
{
	t_app *app;

	app = root();
	obj->path = strdup(path);
	list_push(&app->objs, list_new(obj, sizeof(t_obj*)));
}

t_obj	*get_mesh(const char *path)
{
	t_app	*app;
	t_list	*l;
	t_obj	*obj;

	app = root();
	l = app->objs;
	while (l)
	{
		obj = l->addr;
		if (strcmp(path, obj->path) == 0)
			return (obj);
		l = l->next;
	}
	return (NULL);
}

void 	obj_init_color(t_obj *obj_data)
{
	size_t	i;
	t_vec3f	*addr;
	float	color;

	i = 0;
	while (i < obj_data->nvertices)
	{
		if (i % 3 == 0)
			color = (((float)(rand()%50))/100.0f) + 0.1f;
		addr = (t_vec3f*)&obj_data->colors[i * 3];
		vec3fedit(&addr[0], color, color, color);
		i++;
	}
}

void	obj_init(t_obj *obj_data, t_tmp_obj *t)
{
	obj_data->nvertices = list_length(t->vertexIndices);
	obj_data->vertices = (float*)malloc(sizeof(float) * 3 * obj_data->nvertices);
	obj_data->nuvs = list_length(t->uvIndices);
	if (obj_data->nuvs > 0)
		obj_data->uvs = (float*)malloc(sizeof(float) * 2 * obj_data->nuvs);
	obj_data->nnormals = list_length(t->normalIndices);
	if (obj_data->nnormals > 0)
		obj_data->normals = (float*)malloc(sizeof(float) * 3 * obj_data->nnormals);
	obj_data->tangents = (float*)malloc(sizeof(float) * 3 * obj_data->nnormals);
	obj_data->bitangents = (float*)malloc(sizeof(float) * 3 * obj_data->nnormals);
	obj_data->colors = (float*)calloc(3 * obj_data->nvertices, sizeof(float));
	obj_init_color(obj_data);
}

void	load_all_in_obj(t_obj *obj_data, t_tmp_obj *t)
{
	t->vertexI = t->vI->value;
	if (t->vertexI < 1)
		t->vertexI = list_length(t->temp_vertex) + t->vertexI + 1;
	t->vertex = list_get(t->temp_vertex, t->vertexI - 1);
	obj_data->vertices[t->n * 3 + 0] = t->vertex->x;
	obj_data->vertices[t->n * 3 + 1] = t->vertex->y;
	obj_data->vertices[t->n * 3 + 2] = t->vertex->z;
	if (obj_data->nuvs)
	{
		t->uvI = t->uI->value;
		if (t->uvI < 1)
			t->uvI = list_length(t->temp_uv) + t->uvI + 1;
		t->uv = list_get(t->temp_uv, t->uvI - 1);
		obj_data->uvs[t->n * 2 + 0] = t->uv->x;
		obj_data->uvs[t->n * 2 + 1] = t->uv->y;
	}
	if (obj_data->nnormals)
	{
		t->normalI = t->nI->value;
		if (t->normalI < 1)
			t->normalI = list_length(t->temp_normal) + t->normalI + 1;
		t->normal = list_get(t->temp_normal, t->normalI - 1);
		obj_data->normals[t->n * 3 + 0] = t->normal->x;
		obj_data->normals[t->n * 3 + 1] = t->normal->y;
		obj_data->normals[t->n * 3 + 2] = t->normal->z;
	}
}

void centerobj(t_obj *obj)
{
	size_t i;
	size_t n;

	t_vec3f max;
	t_vec3f min;
	vec3fedit(&max, -1e20f, -1e20f, -1e20f);
	vec3fedit(&min,  1e20f, 1e20f, 1e20f);
	n = obj->nvertices * 3;
	t_vec3f *v;
	i = 0;
	while (i < n)
	{
		v = (t_vec3f*)&obj->vertices[i];
		if (max.x < v->x)
			max.x = v->x;
		if (max.y < v->y)
			max.y = v->y;
		if (max.z < v->z)
			max.z = v->z;
		if (min.x > v->x)
			min.x = v->x;
		if (min.y > v->y)
			min.y = v->y;
		if (min.z > v->z)
			min.z = v->z;
		i+=3;
	}
	t_vec3f *mintomax;
	mintomax = vec3f_new_sub(&max, &min);
	mintomax = vec3f_scale(mintomax, 0.5f);
	mintomax = vec3f_add(mintomax, &min);
	i = 0;
	while (i < n)
	{
		v = (t_vec3f*)&obj->vertices[i];
		vec3f_sub(v, mintomax);
		i+=3;
	}
	free(mintomax);
}

int 	model_load_obj(t_model *model, const char *path)
{
	t_tmp_obj	t;
	t_obj		*obj;

	//Si pas deja charge
	if(!(obj = get_mesh(path)))
	{
		printf("Model loading... %s\n", model->obj_filename);
		//get_mesh(const char *path)
		obj = (t_obj*)malloc(sizeof(t_obj));
		if (obj == NULL)
		{
			printf("Malloc error : exit !\n");
			exit(1);
		}

		if (!tmp_obj_init(&t, path))
			return (0);
		while (tmp_obj_loading(&t))
			;
		t.vI = t.vertexIndices;
		t.uI = t.uvIndices;
		t.nI = t.normalIndices;
		obj_init(obj, &t);
		while (t.n < obj->nvertices)
		{
			if (t.vI == NULL)
				break ;
			load_all_in_obj(obj, &t);
			t.vI = t.vI->next;
			if (t.uI)
				t.uI = t.uI->next;
			if (t.nI)
				t.nI = t.nI->next;
			t.n++;
		}
		obj->mtl = t.mtl;
		tmp_obj_free(&t);

		centerobj(obj);

		if (obj->nvertices > 0 && obj->nuvs > 0 && obj->nvertices == obj->nuvs)
			compute_tangent(obj);
		add_mesh(obj, path);
	}

	//Compat mode
	model->objData = obj;

	model->nvertices = 	obj->nvertices;
	model->vertex = (t_vec3f*)&obj->vertices[0];
	model->color = (t_vec3f*)&obj->colors[0];

	model->enableUV = 0;
	model->enableNormal = 0;
	if (obj->nuvs > 0)
	{
		model->enableUV = 1;
		model->uv = (t_vec2f*)&model->objData->uvs[0];
		model->tangent = (t_vec3f*)&model->objData->tangents[0];
		model->bitangent = (t_vec3f*)&model->objData->bitangents[0];
	}
	else
	{
		model->enableUV = 0;
		model->uv = NULL;//(t_vec2f*)&model->objData->uvs[0]
		model->tangent = NULL;
		model->bitangent = NULL;
	}

	if (model->objData->nnormals > 0)
	{
		model->enableNormal = 1;
		model->normal = (t_vec3f*)&model->objData->normals[0];
	}
	else
	{
		model->enableNormal = 0;
		model->normal = NULL;
	}

	return (1);
}
