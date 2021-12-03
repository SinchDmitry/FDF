/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_grafical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:56:08 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/03 15:16:09 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	is_iso(float *x, float *y, float *z, t_struct_data *map)
{
	t_vls	rot;

	rot.x1 = *x * map->zoom;
	rot.y1 = *y * map->zoom;
	rot.z1 = *z * map->zoom / 2;
	rot.h = (map->height * map->zoom) / 2;
	rot.w = (map->width * map->zoom) / 2;
	*y = (rot.y1 - rot.w) * cos(map->rotX) - rot.z1 * sin(map->rotX);
	*z = (rot.y1 - rot.w) * sin(map->rotX) + rot.z1 * cos(map->rotX);
	rot.y1 = *y;
	rot.z1 = *z;
	*x = (rot.x1 - rot.h) * cos(map->rotY) - rot.z1 * sin(map->rotY);
	*z = (rot.x1 - rot.h) * sin(map->rotY) + rot.z1 * cos(map->rotY);
	rot.x1 = *x;
	rot.z1 = *z;
	*x = (rot.x1) * cos(map->rotZ) - (rot.y1) * sin(map->rotZ);
	*y = (rot.x1) * sin(map->rotZ) + (rot.y1) * cos(map->rotZ);
	if (!map->flag)
	{
		*x = (*x + *y) * cos(map->ang);
		*y = (*x - *y) * sin(map->ang) - *z;
	}
	*x += map->posX;
	*y -= map->posY;
}

static void	init_list(t_line *line, t_vls *xyz, int f)
{
	if (!f)
	{
		line->flag = 0;
		line->deltaX = fabsf(xyz->x2 - xyz->x1);
		line->tmp_delta = line->deltaX;
		line->deltaY = fabsf(xyz->y2 - xyz->y1);
		if (line->deltaX < line->deltaY)
		{
			line->tmp_delta = line->deltaY;
			line->flag = 1;
		}
		line->signX = -1;
		if (xyz->x1 < xyz->x2)
			line->signX = 1;
		line->signY = -1;
		if (xyz->y1 < xyz->y2)
			line->signY = 1;
	}
	else
	{
		line->st_x1 = xyz->x1;
		line->st_x2 = xyz->x2;
		line->st_y1 = xyz->y1;
		line->st_y2 = xyz->y2;
	}
}

void	drawLine(t_vls xyz, t_data *img, t_struct_data *map)
{
	t_line	line_w;

	init_list(&line_w, &xyz, 1);
	is_iso(&xyz.y1, &xyz.x1, &xyz.z1, map);
	is_iso(&xyz.y2, &xyz.x2, &xyz.z2, map);
	init_list(&line_w, &xyz, 0);
	line_w.error = line_w.deltaX - line_w.deltaY;
	while ((int)(xyz.x1 - xyz.x2) || (int)(xyz.y1 - xyz.y2))
	{
		if (xyz.x1 > 1060 || xyz.y1 > 1900 || xyz.x1 < 0 || xyz.y1 < 0)
			break ;
		my_mlx_pixel_put(img, xyz.y1, xyz.x1, grad_col(map, line_w, &xyz));
		line_w.error2 = line_w.error * 2;
		if (line_w.error2 > -line_w.deltaY)
		{
			line_w.error -= line_w.deltaY;
			xyz.x1 += line_w.signX;
		}
		if (line_w.error2 < line_w.deltaX)
		{
			line_w.error += line_w.deltaX;
			xyz.y1 += line_w.signY;
		}
	}
}
