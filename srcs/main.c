#include <scop.h>

void* loadMeshes(void *m)
{
	t_app *app;

	app = (t_app*)m;
	t_list *models;
	int i = 0;
	models = app->models;
	while (models)
	{
		model_load(models->addr);
		models = models->next;
		i++;
	}
	return NULL;
}

char *ft_dirname(const char *filepath)
{
	char *result;
	char **tab;
	int nb;
	int i;

	result = ft_strnew(strlen(filepath));
	tab = ft_strsplit(filepath, '/');
	nb = ft_tablen(tab);
	i = 0;
	while (i < nb - 1)
	{
		if (tab[i])
		{
			strcat(result, tab[i]);
			strcat(result, "/");
		}
		i++;
	}
	ft_tabfree(tab);
	return (result);
}

int main(int argc, char **argv)
{
	t_app *app;
	t_argvise *arg;

	arg = new_argvise(argc, argv);
	app = root();
	app->input = camera_init();
	if (!InitGLFW(app))
	{
		printf("Failed to INIT GLFW\n");
		return (-1);
	}
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	load_bmp("./assets/poney.bmp");
	//printf("%d %s\n", argc, argv[1]);
	if (argc > 1 && argv[1])
		list_push(&app->models, list_new(model_new_scale(argv[1], 1.f,1.f,1.f), sizeof(t_model*)));
	else
		list_push(&app->models, list_new(model_new("./assets/42.obj"), sizeof(t_model*)));
	if (arg->flags['l'])
		list_push(&app->models, list_new(model_new("./assets/light/lantern.obj"), sizeof(t_model*)));
	if (arg->flags['s'])
		list_push(&app->models, list_new(model_new_scale("./assets/skybox/space.obj", 10.0f,10.0f,10.0f), sizeof(t_model*)));
	loadMeshes(app);
	t_list *models;
	int i = 0;
	models = app->models;
	while (models)
	{
		model_bind(models->addr);
		models = models->next;
		i++;
	}

	while(glfwGetKey(app->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(app->window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera_controls(app);
		t_list *models;
		int i = 0;
		models = app->models;
		while (models)
		{
			model_render(app, models->addr);
			models = models->next;
			i++;
		}
		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}
	camera_free(app->input);
	free(arg->flags);
	free(arg->files);
	free(arg);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
	return (0);
}
