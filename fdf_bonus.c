/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:14:26 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/03 18:24:01 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	mlx_draw(t_struct_data *map, t_vls xyz, t_data *img)
{
	if (xyz.y1 != (map->height - 1))
	{
		xyz.y2 = xyz.y1 + 1;
		xyz.x2 = xyz.x1;
		xyz.z2 = map->map_val_col[(int)xyz.y1 + 1][(int)xyz.x1].value;
		xyz.z1 = map->map_val_col[(int)xyz.y1][(int)xyz.x1].value;
		drawLine(xyz, img, map);
	}
	if (xyz.x1 != (map->width - 1))
	{
		xyz.y2 = xyz.y1;
		xyz.x2 = xyz.x1 + 1;
		xyz.z2 = map->map_val_col[(int)xyz.y1][(int)xyz.x1 + 1].value;
		xyz.z1 = map->map_val_col[(int)xyz.y1][(int)xyz.x1].value;
		drawLine(xyz, img, map);
	}
}

void	mlx_line(t_struct_data *map, t_data	*img)
{
	t_vls	xyz;

	xyz.y1 = -1;
	xyz.flag = 1;
	while (++xyz.y1 < map->height)
	{
		xyz.x1 = -1;
		while (++xyz.x1 < map->width)
			mlx_draw(map, xyz, img);
	}
}

void	mlx_run(t_struct_data *map)
{
	t_vars	vars;

	vars.map = map;
	vars.img.mlx = mlx_init();
	vars.img.mlx_win = mlx_new_window(vars.img.mlx, 1920, 1080, "Hello world!");
	vars.img.img = mlx_new_image(vars.img.mlx, 1920, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, \
		&vars.img.line_length, &vars.img.endian);
	mlx_line(vars.map, &vars.img);
	mlx_put_image_to_window(vars.img.mlx, vars.img.mlx_win, vars.img.img, 0, 0);
	mlx_hook(vars.img.mlx_win, 02, (1L << 0), keyboard, &vars);
	mlx_loop(vars.img.mlx);
}

int	main(int argc, char **argv)
{
	char			*line;
	char			**split_arr;
	int				fd;
	t_struct_data	map_data;

	(void)argc;
	split_arr = NULL;
	fd = open(argv[1], O_RDONLY);
	line = reader(fd);
	if (line)
	{
		split_arr = ft_split(line, '\n');
		free(line);
		if (!split_arr)
			return (0);
		map_data.map_val_col = map_struct(split_arr, &map_data);
		init_data(&map_data);
		mlx_run(&map_data);
	}
	return (0);
}
