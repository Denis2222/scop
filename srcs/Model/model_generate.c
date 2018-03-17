#include <scop.h>


void 	model_generate_uniform_model_rotation(t_model *model)
{
	t_mat4f *Rotate;
	t_mat4f *identity;
	t_mat4f *rotatex;
	t_mat4f *rotatey;
	t_mat4f *rotatez;

	rotatex = mat4f_rotate_x(mat4f_identity(1.0f), model->rotation->x);
	rotatey = mat4f_rotate_y(mat4f_identity(1.0f), model->rotation->y);
	rotatez = mat4f_rotate_z(mat4f_identity(1.0f), model->rotation->z);
	identity = mat4f_multiply(rotatex, rotatey);
	Rotate = mat4f_multiply(identity, rotatez);
	glUniformMatrix4fv(model->ModelRotateID, 1, GL_FALSE, &Rotate->m[0][0]);
	free(Rotate);
	free(identity);
	free(rotatex);
	free(rotatey);
	free(rotatez);
}

void 	model_generate_uniform_model(t_model *model)
{
	t_mat4f *Translate;
	t_mat4f *Scale;

	Translate = mat4f_translate(model->position);
	Scale = mat4f_scale(model->scale->x, model->scale->y, model->scale->z);
	glUniformMatrix4fv(model->ModelTranslateID, 1, GL_FALSE, &Translate->m[0][0]);
	glUniformMatrix4fv(model->ModelScaleID, 1, GL_FALSE, &Scale->m[0][0]);
	model_generate_uniform_model_rotation(model);
	free(Translate);
	free(Scale);
}

void 	model_generate_uniform_projection(t_app *app, t_model *model)
{
	t_mat4f *Projection;

	Projection = mat4f_perspective(app->input->initialFoV, 16.0f / 9.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(model->MatrixProjectionID, 1, GL_FALSE, &Projection->m[0][0]);
	free(Projection);
}

void 	model_generate_uniform_view(t_app *app, t_model *model)
{
	t_mat4f *View;
	t_vec3f *target;
	t_vec3f *upVector;

	if (app->input->view)
		target = vec3f_new_add(app->input->pos, app->input->dir);
	else
		target = vec3f(.0f,.0f,.0f);
	upVector = vec3f(0.0f,1.0f,0.0f);
	View = mat4fLookAt(
		app->input->pos,
		target,
		upVector
	);
	glUniformMatrix4fv(model->MatrixViewID, 1, GL_FALSE, &View->m[0][0]);
	free(target);
	free(upVector);
	free(View);
}
