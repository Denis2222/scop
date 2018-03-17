/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 08:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 09:18:04 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_mtl	*mtl_init(void)
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

FILE	*open_file_from_folder(const char *folder, char *path)
{
	char	*dir;
	char	*filepath;
	FILE	*file;

	dir = ft_dirname(folder);
	filepath = (char *)malloc((strlen(dir) + strlen(path) + 5) * sizeof(char));
	bzero(filepath, (strlen(dir) + strlen(path) + 5));
	filepath = strcat(filepath, dir);
	filepath = strcat(filepath, "/");
	filepath = strcat(filepath, path);
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

int		read_mtl_by_line(FILE *file, t_mtl *mtl)
{
	char	line_read[1024];
	int		res;

	res = fscanf(file, "%s", line_read);
	if (res == EOF)
		return (0);
	else if (strcmp(line_read, "map_Kd") == 0)
	{
		fscanf(file, "%s\n", line_read);
		mtl->map_Kd_path = strdup(line_read);
	}
	else if (strcmp(line_read, "map_Ks") == 0)
	{
		fscanf(file, "%s\n", line_read);
		mtl->map_Ks_path = strdup(line_read);
	}
	else if (strcmp(line_read, "map_Bump") == 0)
	{
		fscanf(file, "%s\n", line_read);
		mtl->map_Bump_path = strdup(line_read);
	}
	else
		fgets(line_read, 1024, file);
	return (1);
}

t_mtl	*new_mtl(char *path, t_tmp_obj *t)
{
	t_mtl	*mtl;
	FILE	*file;

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
