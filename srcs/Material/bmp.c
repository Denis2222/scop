/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 09:03:24 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 10:57:11 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

FILE	*read_file(const char *imagepath)
{
	FILE	*file;

	file = fopen(imagepath, "rb");
	if (!file)
	{
		printf("Image could not be opened : %s \n", imagepath);
		return (0);
	}
	return (file);
}

int		load_bmp(const char *imagepath)
{
	unsigned char	header[54];
	unsigned int	d[4];
	unsigned char	*data;
	FILE			*file;

	if (!(file = read_file(imagepath)))
		return (0);
	if (fread(header, 1, 54, file) != 54)
		return (0);
	if (header[0] != 'B' || header[1] != 'M')
		return (0);
	d[0] = *(int*)&(header[0x0A]);
	d[3] = *(int*)&(header[0x22]);
	d[1] = *(int*)&(header[0x12]);
	d[2] = *(int*)&(header[0x16]);
	if (d[3] == 0)
		d[3] = d[1] * d[2] * 3;
	data = (unsigned char*)malloc(d[3]);
	if (!data)
		return (0);
	fread(data, 1, d[3], file);
	fclose(file);
	add_texture((char *)imagepath, data, d[1], d[2]);
	return (1);
}
