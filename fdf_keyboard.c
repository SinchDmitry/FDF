/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:46:08 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/03 19:31:14 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_data(t_struct_data	*data)
{
	int	tmp;

	data->posX = 1000;
	data->posY = -550;
	data->zoom = 1;
	tmp = data->width;
	if (data->height > data->width)
		tmp = data->height;
	if (tmp <= 400)
		data->zoom = 400 / tmp;
	data->rotX = 0;
	data->rotY = 0;
	data->rotZ = 0;
	data->ang = 0.5;
	data->flag = 0;
}

static void	close_file(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->map->height)
		free (vars->map->map_val_col[i]);
	free (vars->map->map_val_col);
	mlx_destroy_window(vars->img.mlx, vars->img.mlx_win);
	exit (0);
}

static void	keycode_rot(int keycode, t_vars *vars)
{
	if (keycode == 18)
		vars->map->f_grad += 1;
	if (!vars->map->flag)
	{
		if (keycode == 6)
			vars->map->rotX += 0.05;
		else if (keycode == 14)
			vars->map->rotX -= 0.05;
		else if (keycode == 2)
			vars->map->rotZ += 0.05;
		else if (keycode == 0)
			vars->map->rotZ -= 0.05;
		else if (keycode == 13)
			vars->map->rotY += 0.05;
		else if (keycode == 7)
			vars->map->rotY -= 0.05;
		else if (keycode == 12)
			vars->map->ang += 0.05;
		else if (keycode == 8)
			vars->map->ang -= 0.05;
	}
}

static void	keycode_num(int keycode, t_vars *vars)
{
	if (keycode == 126)
		vars->map->posY += 50;
	else if (keycode == 125)
		vars->map->posY -= 50;
	else if (keycode == 123)
		vars->map->posX -= 50;
	else if (keycode == 124)
		vars->map->posX += 50;
	else if (keycode == 69)
		vars->map->zoom += 1;
	else if (keycode == 78 && vars->map->zoom > 0)
		vars->map->zoom -= 1;
	else if (keycode == 1)
		init_data(vars->map);
	else if (keycode == 53)
		close_file(vars);
	if (keycode == 19)
	{
		init_data(vars->map);
		vars->map->flag = 1;
	}
	else if (keycode == 20)
		vars->map->flag = 0;
	keycode_rot(keycode, vars);
}

int	keyboard(int keycode, t_vars *vars)
{
	mlx_clear_window(vars->img.mlx, vars->img.mlx_win);
	keycode_num(keycode, vars);
	vars->img.img = mlx_new_image(vars->img.mlx, 1920, 1080);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	mlx_line(vars->map, &vars->img);
	mlx_put_image_to_window(vars->img.mlx, vars->img.mlx_win, vars->img.img, \
		 0, 0);
	return (0);
}
