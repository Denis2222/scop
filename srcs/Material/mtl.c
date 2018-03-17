#include <scop.h>

void mtl_print(t_mtl *mtl)
{
	printf("MTL:\n");
	printf("name:%s\n", mtl->name);
	printf("Ns:%f\n",   mtl->Ns);

	if (mtl->Ka)
	{
		printf("Ka:");
		vec3f_print(mtl->Ka);
	}

	if (mtl->Kd)
	{
		printf("Kd:");
		vec3f_print(mtl->Kd);
	}
	if (mtl->Ks)
	{
		printf("Ks:");
		vec3f_print(mtl->Ks);
	}
	if (mtl->Ke)
	{
		printf("Ke:");
		vec3f_print(mtl->Ke);
	}
	printf("Ni:%f\n",			   mtl->Ni);
	printf("d:%f\n",			   mtl->d);
	printf("illum:%d\n",		   mtl->illum);
	printf("map_Kd_path:%s\n",     mtl->map_Kd_path);
	printf("map_Ks_path:%s\n",     mtl->map_Ks_path);
	printf("map_Bump_path:%s\n",   mtl->map_Bump_path);
}

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

t_mtl *new_mtl(char *path, t_tmp_obj *t)
{
	t_mtl *mtl;

	mtl = mtl_init(void);

	char *dir = ft_dirname(t->path);
	char *filepath = (char *)malloc((strlen(dir) + strlen(path) + 5) * sizeof(char));
	bzero(filepath, (strlen(dir) + strlen(path) + 5));
	filepath = strcat(filepath,dir);
	filepath = strcat(filepath,"/");
	filepath = strcat(filepath,path);

	FILE *file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("Impossible to open mtl file %s !\n", filepath);
		free(filepath);
		free(dir);
		return (0);
	}
	free(filepath);
	free(dir);
	while (1)
	{
		char lineRead[1024];
		int res = fscanf(file, "%s", lineRead);
		if (res == EOF)
			break;
		if (strcmp(lineRead, "newmtl") == 0) {
			fscanf(file, "%s\n",lineRead);
			mtl->name = strdup(lineRead);
/*		} else if (strcmp(lineRead, "Ns") == 0) {
			fscanf(file, "%f\n",&mtl->Ns);
		} else if (strcmp(lineRead, "Ka") == 0) {
			mtl->Ka = vec3f(0.f,0.f,0.f);
			fscanf(file, "%f %f %f\n", &mtl->Ka->x, &mtl->Ka->y, &mtl->Ka->z);
		} else if (strcmp(lineRead, "Kd") == 0) { //"Kd" couleur diffuse (la couleur de l'objet sous lumière blanche) t_vec3
			mtl->Kd = vec3f(0.f,0.f,0.f);
			fscanf(file, "%f %f %f\n", &mtl->Kd->x, &mtl->Kd->y, &mtl->Kd->z);
		} else if (strcmp(lineRead, "Ks") == 0) {	//"Ks" couleur spéculaire (specular)  t_vec3
			mtl->Ks = vec3f(0.f,0.f,0.f);
			fscanf(file, "%f %f %f\n", &mtl->Ks->x, &mtl->Ks->y, &mtl->Ks->z);
		} else if (strcmp(lineRead, "Ke") == 0) {	//"Ke" couleur émissive (emissive)		t_vec3
			mtl->Ke = vec3f(0.f,0.f,0.f);
			fscanf(file, "%f %f %f\n", &mtl->Ke->x, &mtl->Ke->y, &mtl->Ke->z);
		} else if (strcmp(lineRead, "Ni") == 0) {
				fscanf(file, "%f\n", &mtl->Ni);
		} else if (strcmp(lineRead, "d") == 0) {
			fscanf(file, "%f\n", &mtl->d);
		} else if (strcmp(lineRead, "illum") == 0) {
			fscanf(file, "%d\n", &mtl->illum);*/
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
	}
	if (mtl->map_Kd_path)
		mtl->map_Kd_path = load_texture(mtl->map_Kd_path, t);
	if (mtl->map_Bump_path)
		mtl->map_Bump_path = load_texture(mtl->map_Bump_path, t);
	if (mtl->map_Ks_path)
		mtl->map_Ks_path = load_texture(mtl->map_Ks_path, t);
	return (mtl);
}
