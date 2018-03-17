#include <scop.h>

void model_send_buffer(unsigned int attr, GLuint *buffer, size_t size)
{
	glEnableVertexAttribArray(attr);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glVertexAttribPointer(attr,	size, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void model_send_texture(unsigned int i, GLuint Texture, GLuint TextureID)
{
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(TextureID, i);
}

void model_send_mvp(t_app *app, t_model *model)
{
	model_generate_uniform_model(model);
	model_generate_uniform_view(app, model);
	model_generate_uniform_projection(app, model);
}
