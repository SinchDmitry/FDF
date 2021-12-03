/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:11:00 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/03 18:24:11 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	parsing_RGB(int color, int *Rbyte, int *Gbyte, int *Bbyte)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	*Rbyte = 0;
	*Gbyte = 0;
	*Bbyte = 0;
	while (++j >= 0 && i < 8)
		if (color & (1 << i++))
			*Rbyte = (*Rbyte | (1 << j));
	j = -1;
	while (++j >= 0 && i < 16)
		if (color & (1 << i++))
			*Gbyte = (*Gbyte | (1 << j));
	j = -1;
	while (++j >= 0 && i < 24)
		if (color & (1 << i++))
			*Bbyte = (*Bbyte | (1 << j));
}

static int	RGB_to_DEC(int Rbyte, int Gbyte, int Bbyte)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	color = 0;
	while (i++ < 8)
		if (Rbyte & (1 << j++))
			color = (color | (1 << (i - 1)));
	j = 0;
	while (i++ < 16)
		if (Gbyte & (1 << j++))
			color = (color | (1 << (i - 1)));
	j = 0;
	while (i++ < 24)
		if (Bbyte & (1 << j++))
			color = (color | (1 << (i - 1)));
	return (color);
}

static void	col_to_RGB(t_struct_data *map, t_line line, t_vls *xyz)
{
	int	color1;
	int	color2;

	color1 = map->map_val_col[(int)line.st_y1][(int)line.st_x1].color;
	color2 = map->map_val_col[(int)line.st_y2][(int)line.st_x2].color;
	parsing_RGB(color1, &xyz->Rbyte1, &xyz->Gbyte1, &xyz->Bbyte1);
	parsing_RGB(color2, &xyz->Rbyte2, &xyz->Gbyte2, &xyz->Bbyte2);
	xyz->flag = 0;
}

void	tmp_color_operation(t_vls *xyz, float k)
{
	xyz->Rbyte = xyz->Rbyte1 + k * (xyz->Rbyte2 - xyz->Rbyte1);
	xyz->Gbyte = xyz->Gbyte1 + k * (xyz->Gbyte2 - xyz->Gbyte1);
	xyz->Bbyte = xyz->Bbyte1 + k * (xyz->Bbyte2 - xyz->Bbyte1);
}

int	grad_col(t_struct_data *map, t_line line, t_vls *xyz)
{
	float	tmp1;
	float	tmp2;
	int		color;
	float	k;

	tmp1 = map->map_val_col[(int)line.st_y2][(int)line.st_x2].color;
	color = map->map_val_col[(int)line.st_y1][(int)line.st_x1].color;
	if (color != tmp1 && (map->f_grad % 2))
	{
		tmp1 = xyz->x1;
		tmp2 = xyz->x2;
		if (line.flag)
		{
			tmp1 = xyz->y1;
			tmp2 = xyz->y2;
		}
		if (xyz->flag)
			col_to_RGB(map, line, xyz);
		k = (1 - fabsf(tmp1 - tmp2) / line.tmp_delta);
		tmp_color_operation(xyz, k);
		color = RGB_to_DEC(xyz->Rbyte, xyz->Gbyte, xyz->Bbyte);
	}
	return (color);
}
