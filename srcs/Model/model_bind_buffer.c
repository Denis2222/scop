/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_bind_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:14:38 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:15:28 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_bind_buffer_all(t_model *model)
{
	model_bind_buffer(&model->vertexbuffer,
		sizeof(float) * 3 * model->objData->nvertices, (float*)model->vertex);
	model_bind_buffer(&model->colorbuffer,
		sizeof(float) * 3 * model->objData->nvertices, (float*)model->color);
	if (model->enableUV)
		model_bind_buffer(&model->uvbuffer,
			sizeof(float) * 2 * model->objData->nuvs, (float*)model->uv);
	if (model->enableNormal)
		model_bind_buffer(&model->normalbuffer, sizeof(float) * 3 *
		model->objData->nnormals, (float*)model->normal);
	if (model->enableUV)
	{
		model_bind_buffer(&model->tangentbuffer, sizeof(float) * 3 *
		model->objData->nvertices, (float*)model->tangent);
		model_bind_buffer(&model->bitangentbuffer, sizeof(float) * 3 *
		model->objData->nvertices, (float*)model->bitangent);
	}
}

void	model_bind_buffer(GLuint *buffer, size_t s, float *data)
{
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, s, data, GL_STATIC_DRAW);
}
