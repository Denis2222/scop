#include <scop.h>

int		model_bind(t_model *model)
{
	t_obj *obj;

	if (!model->loaded)
		return (0);
	obj = model->objData;
	if (obj->mtl)
	{
		if(obj->mtl->map_Kd_path)
			model_bind_texture(&obj->mtl->map_Kd, obj->mtl->map_Kd_path);
		if(obj->mtl->map_Ks_path)
			model_bind_texture(&obj->mtl->map_Ks, obj->mtl->map_Ks_path);
		if(obj->mtl->map_Bump_path)
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
	if (obj->mtl)
	{
		if (obj->mtl->map_Kd)
			model->DiffuseTexture = obj->mtl->map_Kd;
		if (obj->mtl->map_Bump)
			model->NormalTexture = obj->mtl->map_Bump;
		if (obj->mtl->map_Ks)
			model->SpecularTexture = obj->mtl->map_Ks;
	}
	model->MatrixViewID =  		glGetUniformLocation(model->programID, "V");
	model->MatrixProjectionID = glGetUniformLocation(model->programID, "P");
	model->DiffuseTextureID  = glGetUniformLocation(model->programID, "DiffuseTextureSampler");
	model->NormalTextureID   = glGetUniformLocation(model->programID, "NormalTextureSampler");
	model->SpecularTextureID = glGetUniformLocation(model->programID, "SpecularTextureSampler");
	model->ModelScaleID = glGetUniformLocation(model->programID, "ModelScale");
	model->ModelRotateID = glGetUniformLocation(model->programID, "ModelRotate");
	model->ModelTranslateID = glGetUniformLocation(model->programID, "ModelTranslate");
	model->LightID			 = glGetUniformLocation(model->programID, "LightPosition_worldspace");
	model->RatioColorTextureID		 = glGetUniformLocation(model->programID, "RatioColorTexture");
	model_bind_buffer(&model->vertexbuffer, sizeof(float) * 3 * model->objData->nvertices, (float*)model->vertex);
	model_bind_buffer(&model->colorbuffer, sizeof(float) * 3 * model->objData->nvertices, (float*)model->color);
	if (model->enableUV)
		model_bind_buffer(&model->uvbuffer, sizeof(float) * 2 * model->objData->nuvs, (float*)model->uv);
	if (model->enableNormal)
		model_bind_buffer(&model->normalbuffer, sizeof(float) * 3 * model->objData->nnormals, (float*)model->normal);
	if (model->enableUV)
	{
		model_bind_buffer(&model->tangentbuffer, sizeof(float) * 3 * model->objData->nvertices, (float*)model->tangent);
		model_bind_buffer(&model->bitangentbuffer, sizeof(float) * 3 * model->objData->nvertices, (float*)model->bitangent);
	}
	return (1);
}

void 	model_bind_texture(GLuint *textureID, char *path)
{
	t_texture *texture;

	texture = get_texture(path);
	if (!texture)
		return ;
	glGenTextures(1, &texture->textureID);
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	*textureID = texture->textureID;
}

void 	model_bind_buffer(GLuint *buffer, size_t s, float *data)
{
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, s, data, GL_STATIC_DRAW);
}

int 	model_bind_shader(t_model *model, char *name)
{
	model->programID = shader_load(name);
	if (model->programID == 0)
	{
		printf("Shader loading Error !\n");
		return (0);
	}
	return (1);
}
