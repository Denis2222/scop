/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:15:45 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:15:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_free(t_model *model)
{
	if (model->objData->nvertices)
	{
		free(model->objData->vertices);
		free(model->objData->tangents);
		free(model->objData->bitangents);
	}
	if (model->objData->nuvs)
		free(model->objData->uvs);
	if (model->objData->nnormals)
		free(model->objData->normals);
	free(model->position);
	free(model->rotation);
	free(model->scale);
	free(model->objData);
}
