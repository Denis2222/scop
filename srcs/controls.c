/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:30:15 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:26:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void 	camera_free(t_input *input)
{
	free(input->pos);
	free(input->dir);
	free(input->right);
	free(input->deltaDir);
	free(input->deltaRight);
	free(input->lightPos);
	free(input);
}

t_input *camera_init(void)
{
	t_input *in;

	in = (t_input*)malloc(sizeof(t_input));
	if (!in)
	{
		printf("Malloc Error\n");
		exit(1);
	}
	in->lastTime = glfwGetTime();
	in->horizontalAngle = 7.2f;
	in->verticalAngle = 3.6f;
	in->initialFoV = BASE_FOV;
	in->speed = 10.0f; // 3 units / second
	in->mouseSpeed = 0.025f;
	in->pos = vec3f(10.0f,3.0f,3.0f);
	in->dir = vec3f(1.0f,0.0f,0.0f);
	in->right = vec3f(0.0f,0.0f,0.0f);
	in->deltaDir = vec3f(0.0f,0.0f,0.0f);;
	in->deltaRight = vec3f(0.0f,0.0f,0.0f);;
	in->view = 0;
	in->lightPos = vec3f(4.0f,4.0f,4.0f);
	in->var = 0.0f;
	in->renderMode = GL_TRIANGLES;
	in->autoRotate = 1;
	in->skybox = 0;
	in->RatioColorTextureBool = 1;
	in->RatioColorTexture = 1.0f;
	return (in);
}

void light_controls(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_KP_8) == GLFW_PRESS){
		vec3fedit(app->input->lightPos, app->input->lightPos->x + 0.2f, app->input->lightPos->y, app->input->lightPos->z);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_2) == GLFW_PRESS){
		vec3fedit(app->input->lightPos, app->input->lightPos->x - 0.2f, app->input->lightPos->y, app->input->lightPos->z);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_6) == GLFW_PRESS){
		vec3fedit(app->input->lightPos, app->input->lightPos->x, app->input->lightPos->y, app->input->lightPos->z + 0.2f);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_4) == GLFW_PRESS){
		vec3fedit(app->input->lightPos, app->input->lightPos->x, app->input->lightPos->y, app->input->lightPos->z - 0.2f);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_7) == GLFW_PRESS){
		vec3fedit(app->input->lightPos, app->input->lightPos->x, app->input->lightPos->y + 0.2f, app->input->lightPos->z);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_1) == GLFW_PRESS){
		vec3fedit(app->input->lightPos, app->input->lightPos->x, app->input->lightPos->y - 0.2f, app->input->lightPos->z);
	}
}

void camera_controls(t_app *app)
{
	float	deltaTime;
	double	xpos;
	double	ypos;

	glfwGetCursorPos(app->window, &xpos, &ypos);
	deltaTime = (glfwGetTime() - app->input->lastTime);
	light_controls(app);
	app->input->lastTime = glfwGetTime();
	glfwSetCursorPos(app->window, WIDTH/2, HEIGHT/2);

	app->input->horizontalAngle += app->input->mouseSpeed * deltaTime * (float)(WIDTH/2 - xpos );
	app->input->verticalAngle   += app->input->mouseSpeed * deltaTime * (float)( HEIGHT/2 - ypos );

	vec3fedit(app->input->dir,  cos(app->input->verticalAngle) * sin(app->input->horizontalAngle),
								sin(app->input->verticalAngle),
								cos(app->input->verticalAngle) * cos(app->input->horizontalAngle)
	);

	vec3fedit(app->input->right,sin(app->input->horizontalAngle - 3.14f/2.0f),
								0,
								cos(app->input->horizontalAngle - 3.14f/2.0f)
	);

	vec3fedit(app->input->deltaDir,
			app->input->dir->x * deltaTime * app->input->speed,
			app->input->dir->y * deltaTime * app->input->speed,
			app->input->dir->z * deltaTime * app->input->speed);

	vec3fedit(app->input->deltaRight,
			app->input->right->x * deltaTime * app->input->speed,
			app->input->right->y * deltaTime * app->input->speed,
			app->input->right->z * deltaTime * app->input->speed);
	if (glfwGetKey(app->window, GLFW_KEY_UP ) == GLFW_PRESS){
		vec3f_add(app->input->pos, app->input->deltaDir);
	}
	if (glfwGetKey(app->window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		vec3f_sub(app->input->pos, app->input->deltaDir);
	}
	if (glfwGetKey(app->window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
	  	vec3f_add(app->input->pos, app->input->deltaRight);
	}
	if (glfwGetKey(app->window, GLFW_KEY_LEFT ) == GLFW_PRESS){
	  	vec3f_sub(app->input->pos, app->input->deltaRight);
	}

	if (glfwGetKey(app->window, GLFW_KEY_V ) == GLFW_PRESS){
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_V) == GLFW_RELEASE && oldState == GLFW_PRESS) {
		   if (app->input->view == 0)
			   app->input->view = 1;
		   else
			   app->input->view = 0;
		}
		oldState = glfwGetKey(app->window, GLFW_KEY_V);
	}

	if (glfwGetKey(app->window, GLFW_KEY_M ) == GLFW_PRESS){
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_M) == GLFW_RELEASE && oldState == GLFW_PRESS) {
		   app->input->renderMode++;
		   app->input->renderMode = app->input->renderMode%12;
		}
		oldState = glfwGetKey(app->window, GLFW_KEY_M);
	}

	if (glfwGetKey(app->window, GLFW_KEY_T ) == GLFW_PRESS){
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_T) == GLFW_RELEASE && oldState == GLFW_PRESS) {
			app->input->RatioColorTextureBool = app->input->RatioColorTextureBool ? 0 : 1;
		}
	}

	if (glfwGetKey(app->window, GLFW_KEY_K ) == GLFW_PRESS){
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_K) == GLFW_RELEASE && oldState == GLFW_PRESS) {
			app->input->autoRotate = app->input->autoRotate ? 0 : 1;
		}
	}

	if (glfwGetKey(app->window, GLFW_KEY_L ) == GLFW_PRESS){
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_L) == GLFW_RELEASE && oldState == GLFW_PRESS) {
			app->input->skybox = app->input->skybox ? 0 : 1;
		}
	}

	if (app->input->RatioColorTextureBool && app->input->RatioColorTexture <= 1)
		app->input->RatioColorTexture+=0.01;
	else if (app->input->RatioColorTexture >= 0)
		app->input->RatioColorTexture-=0.01;
}
