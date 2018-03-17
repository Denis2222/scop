#include <scop.h>

char *load_texture(char *path, t_tmp_obj *t)
{
	char *filepath;
	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		char *dir = ft_dirname(t->path);
		filepath = (char *)malloc((strlen(dir) + strlen(path) + 5) * sizeof(char));
		bzero(filepath, (strlen(dir) + strlen(path) + 5));
		filepath = strcat(filepath,dir);
		filepath = strcat(filepath,"/");
		filepath = strcat(filepath,path);
		file = fopen(filepath, "r");
		free(dir);
		free(path);
		path = filepath;
		if (file == NULL)
		{
			free(filepath);
			printf("Impossible to open texture file : %s !\n", filepath);
			return (path);
		}
	}
	if (get_texture(path))
	{
		printf("Texture Already load ! ");
		return (path);
	}
	if (!(loadBMP_custom(path)))
	{
		printf("Texture %s  Not Found  Or not correct Format !\n", path);
		return (path);
	}
	return (path);
}

int loadBMP_custom(const char * imagepath){
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;

	FILE * file = fopen(imagepath,"rb");
	if (!file)
	{
		printf(              "Image could not be opened : %s \n", imagepath);
		return (0);
	}
	if ( fread(header, 1, 54, file)!=54 )
	    return (0);
	if ( header[0] != 'B' || header[1] != 'M')
	    return (0);
	printf("		%s\n", imagepath);
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	if (imageSize==0)
		imageSize = width * height * 3;
	if (dataPos==0)
		dataPos = 54;
	data = (unsigned char*)malloc(imageSize);
	if (!data)
		return (0);
	fread(data,1,imageSize,file);
	fclose(file);
	add_texture((char *)imagepath, data, width, height);
	return (1);
}
