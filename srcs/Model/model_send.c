/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:15:57 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:18:33 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_send_buffer(unsigned int attr, GLuint *buffer, size_t size)
{
	glEnableVertexAttribArray(attr);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glVertexAttribPointer(attr, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void	model_send_texture(unsigned int i, GLuint texture, GLuint texture_id)
{
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texture_id, i);
}

void	model_send_mvp(t_app *app, t_model *model)
{
	model_generate_uniform_model(model);
	model_generate_uniform_view(app, model);
	model_generate_uniform_projection(app, model);
}
