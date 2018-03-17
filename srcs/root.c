#include <scop.h>

t_app	*root(void)
{
	static t_app	*app = 0;

	if (app == 0)
	{
		app = (t_app*)malloc(sizeof(t_app));
		if (!app)
		{
			printf("General malloc fail root \n");
			exit(1);
		}
		app->models = NULL;
		app->textures = NULL;
		app->objs = NULL;
		app->shaders = NULL;
	}
	return app;
}
