#include <scop.h>

void		add_texture(char *path, unsigned char *data, int width, int height)
{
	t_texture	*t;
	t_app		*app;

	t = (t_texture*)malloc(sizeof(t_texture));
	if (!t)
	{
		printf("Erreur malloc add texture ! \n");
		exit(1);
	}
	t->path = strdup(path);
	t->data = data;
	t->width = width;
	t->height = height;
	t->textureID = 0;
	t->loaded = 0;
	app = root();
	list_push(&app->textures, list_new(t, sizeof(t_texture*)));
}

t_texture	*get_texture(char *path)
{
	t_list		*l;
	t_texture	*t;
	t_app		*app;

	app = root();
	l = app->textures;
	while (l)
	{
		t = l->addr;
		if (strcmp(path, t->path) == 0)
			return (t);
		l = l->next;
	}
	return (NULL);
}
