/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_bind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:03:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 17:33:20 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_bind_uniform(t_model *model)
{
	model->matrix_view_id = glGetUniformLocation(model->program_id, "V");
	model->matrix_projection_id = glGetUniformLocation(model->program_id, "P");
	model->diffuse_texture_id = glGetUniformLocation(model->program_id,
		"diffuse_textureSampler");
	model->normal_texture_id = glGetUniformLocation(model->program_id,
		"normal_textureSampler");
	model->specular_texture_id = glGetUniformLocation(model->program_id,
		"specular_textureSampler");
	model->model_scale_id = glGetUniformLocation(model->program_id,
		"ModelScale");
	model->model_rotate_id = glGetUniformLocation(model->program_id,
		"ModelRotate");
	model->model_translate_id = glGetUniformLocation(model->program_id,
		"ModelTranslate");
	model->light_id = glGetUniformLocation(model->program_id,
		"LightPosition_worldspace");
	model->ratio_colortexture_id = glGetUniformLocation(model->program_id,
		"ratio_color_texture");
}

void	model_bind_texture_to_uniform(t_model *model, t_obj *obj)
{
	if (obj->mtl)
	{
		if (obj->mtl->map_kd)
			model->diffuse_texture = obj->mtl->map_kd;
		if (obj->mtl->map_bump)
			model->normal_texture = obj->mtl->map_bump;
		if (obj->mtl->map_ks)
			model->specular_texture = obj->mtl->map_ks;
	}
	model_bind_uniform(model);
	model_bind_buffer_all(model);
}

int		model_bind(t_model *model)
{
	t_obj *obj;

	if (!model->loaded)
		return (0);
	obj = model->obj_data;
	if (obj->mtl)
	{
		if (obj->mtl->map_kd_path)
			model_bind_texture(&obj->mtl->map_kd, obj->mtl->map_kd_path);
		if (obj->mtl->map_ks_path)
			model_bind_texture(&obj->mtl->map_ks, obj->mtl->map_ks_path);
		if (obj->mtl->map_bump_path)
			model_bind_texture(&obj->mtl->map_bump, obj->mtl->map_bump_path);
	}
	if (obj->mtl && obj->mtl->map_bump && obj->mtl->map_kd)
		model_bind_shader(model, "Normal");
	else if (obj->mtl && obj->mtl->map_kd)
		model_bind_shader(model, "Shading");
	else
	{
		model_bind_shader(model, "Color");
		model_bind_texture(&model->diffuse_texture, "./assets/poney.bmp");
	}
	model_bind_texture_to_uniform(model, obj);
	return (1);
}

void	model_bind_texture(GLuint *texture_id, char *path)
{
	t_texture	*texture;

	texture = get_texture(path);
	if (!texture)
		return ;
	glGenTextures(1, &texture->texture_id);
	glBindTexture(GL_TEXTURE_2D, texture->texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
		0, GL_BGR, GL_UNSIGNED_BYTE, texture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	*texture_id = texture->texture_id;
}

int		model_bind_shader(t_model *model, char *name)
{
	model->program_id = shader_load(name);
	if (model->program_id == 0)
	{
		printf("Shader loading Error !\n");
		return (0);
	}
	return (1);
}
