/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_bind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:03:54 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:31:33 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_bind_uniform(t_model *model)
{
	model->MatrixViewID = glGetUniformLocation(model->programID, "V");
	model->MatrixProjectionID = glGetUniformLocation(model->programID, "P");
	model->DiffuseTextureID = glGetUniformLocation(model->programID,
		"DiffuseTextureSampler");
	model->NormalTextureID = glGetUniformLocation(model->programID,
		"NormalTextureSampler");
	model->SpecularTextureID = glGetUniformLocation(model->programID,
		"SpecularTextureSampler");
	model->ModelScaleID = glGetUniformLocation(model->programID,
		"ModelScale");
	model->ModelRotateID = glGetUniformLocation(model->programID,
		"ModelRotate");
	model->ModelTranslateID = glGetUniformLocation(model->programID,
		"ModelTranslate");
	model->LightID = glGetUniformLocation(model->programID,
		"LightPosition_worldspace");
	model->RatioColorTextureID = glGetUniformLocation(model->programID,
		"RatioColorTexture");
}

void	model_bind_texture_to_uniform(t_model *model, t_obj *obj)
{
	if (obj->mtl)
	{
		if (obj->mtl->map_Kd)
			model->DiffuseTexture = obj->mtl->map_Kd;
		if (obj->mtl->map_Bump)
			model->NormalTexture = obj->mtl->map_Bump;
		if (obj->mtl->map_Ks)
			model->SpecularTexture = obj->mtl->map_Ks;
	}
	model_bind_uniform(model);
	model_bind_buffer_all(model);
}

int		model_bind(t_model *model)
{
	t_obj *obj;

	if (!model->loaded)
		return (0);
	obj = model->objData;
	if (obj->mtl)
	{
		if (obj->mtl->map_Kd_path)
			model_bind_texture(&obj->mtl->map_Kd, obj->mtl->map_Kd_path);
		if (obj->mtl->map_Ks_path)
			model_bind_texture(&obj->mtl->map_Ks, obj->mtl->map_Ks_path);
		if (obj->mtl->map_Bump_path)
			model_bind_texture(&obj->mtl->map_Bump, obj->mtl->map_Bump_path);
	}
	if (obj->mtl && obj->mtl->map_Bump && obj->mtl->map_Kd)
		model_bind_shader(model, "Normal");
	else if (obj->mtl && obj->mtl->map_Kd)
		model_bind_shader(model, "Shading");
	else
	{
		model_bind_shader(model, "Color");
		model_bind_texture(&model->DiffuseTexture, "./assets/poney.bmp");
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
	glGenTextures(1, &texture->textureID);
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
		0, GL_BGR, GL_UNSIGNED_BYTE, texture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	*texture_id = texture->textureID;
}

int		model_bind_shader(t_model *model, char *name)
{
	model->programID = shader_load(name);
	if (model->programID == 0)
	{
		printf("Shader loading Error !\n");
		return (0);
	}
	return (1);
}
