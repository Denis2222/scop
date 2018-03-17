#include <scop.h>

t_mtl *mtl_init(void)
{
	t_mtl *mtl;

	mtl = (t_mtl*)malloc(sizeof(t_mtl));
	mtl->name = NULL;
	mtl->Ns = 0.0f;
	mtl->Ka = NULL;
	mtl->Kd = NULL;
	mtl->Ks = NULL;
	mtl->Ke = NULL;
	mtl->Ni = 0.0f;
	mtl->d = 0.0f;
	mtl->illum = 0;
	mtl->map_Kd_path = NULL;
	mtl->map_Ks_path = NULL;
	mtl->map_Bump_path = NULL;
	mtl->map_Kd_buffer = NULL;
	mtl->map_Ks_buffer = NULL;
	mtl->map_Bump_buffer = NULL;
	mtl->map_Kd = 0;
	mtl->map_Ks = 0;
	mtl->map_Bump = 0;
	return (mtl);
}


FILE *open_file_from_folder(const char *folder, char *path)
{
	char	*dir;
	char	*filepath;
	FILE	*file;

	dir = ft_dirname(folder);
	filepath = (char *)malloc((strlen(dir) + strlen(path) + 5) * sizeof(char));
	bzero(filepath, (strlen(dir) + strlen(path) + 5));
	filepath = strcat(filepath,dir);
	filepath = strcat(filepath,"/");
	filepath = strcat(filepath,path);
	file = fopen(filepath, "r");
	if (file == NULL)
	{
		free(filepath);
		free(dir);
		return (0);
	}
	free(filepath);
	free(dir);
	return (file);
}


int read_mtl_by_line(FILE *file, t_mtl *mtl)
{
	char lineRead[1024];
	int res = fscanf(file, "%s", lineRead);
	if (res == EOF)
		return (0);
	if (strcmp(lineRead, "newmtl") == 0) {
		fscanf(file, "%s\n",lineRead);
		mtl->name = strdup(lineRead);
	} else if (strcmp(lineRead, "map_Kd") == 0) {
		fscanf(file, "%s\n", lineRead);
		mtl->map_Kd_path = strdup(lineRead);
	} else if (strcmp(lineRead, "map_Ks") == 0) {
		fscanf(file, "%s\n", lineRead);
		mtl->map_Ks_path = strdup(lineRead);
	} else if (strcmp(lineRead, "map_Bump") == 0) {
		fscanf(file, "%s\n", lineRead);
		mtl->map_Bump_path = strdup(lineRead);
	} else
		fgets(lineRead, 1024, file);
	return (1);
}

t_mtl *new_mtl(char *path, t_tmp_obj *t)
{
	t_mtl *mtl;
	FILE *file;

	if (!(file = open_file_from_folder(t->path, path)))
	{
		printf("Impossible to open mtl file %s from %s !\n", path, t->path);
		return (NULL);
	}
	mtl = mtl_init();
	while (read_mtl_by_line(file, mtl))
		;
	fclose(file);
	if (mtl->map_Kd_path)
		mtl->map_Kd_path = load_texture(mtl->map_Kd_path, t);
	if (mtl->map_Bump_path)
		mtl->map_Bump_path = load_texture(mtl->map_Bump_path, t);
	if (mtl->map_Ks_path)
		mtl->map_Ks_path = load_texture(mtl->map_Ks_path, t);
	return (mtl);
}
