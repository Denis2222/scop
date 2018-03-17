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
	if (model->obj_data->nvertices)
	{
		free(model->obj_data->vertices);
		free(model->obj_data->tangents);
		free(model->obj_data->bitangents);
	}
	if (model->obj_data->nuvs)
		free(model->obj_data->uvs);
	if (model->obj_data->nnormals)
		free(model->obj_data->normals);
	free(model->position);
	free(model->rotation);
	free(model->scale);
	free(model->obj_data);
}
