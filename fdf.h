/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:14:29 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/03 15:51:44 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "math.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <mlx.h>
# include <stdio.h>

# define BUF_SIZE 10000
# define SCL 8
# define STD_COLOR 16777215 
// - white 16776960 //- yellow  255 //- blue 16711680 //- red  16519104 //- pink

typedef struct s_struct
{
	int	value;
	int	color;
}	t_struct;

typedef struct s_data
{
	void	*img;
	char	*addr;
	void	*mlx;
	void	*mlx_win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_struct_data
{
	int			width;
	int			height;
	int			posX;
	int			posY;
	int			zoom;
	float		rotX;
	float		rotY;
	float		rotZ;
	float		ang;
	int			flag;
	int			f_grad;
	t_struct	**map_val_col;
}	t_struct_data;

typedef struct s_line
{
	float	deltaX;
	float	deltaY;
	float	tmp_delta;
	float	signX;
	float	signY;
	float	error;
	float	error2;
	int		flag;
	float	st_x1;
	float	st_x2;
	float	st_y1;
	float	st_y2;
}	t_line;

typedef struct s_vars {
	t_data			img;
	t_struct_data	*map;
}	t_vars;

typedef struct s_vls
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	z1;
	float	z2;
	int		Rbyte;
	int		Gbyte;
	int		Bbyte;
	int		Rbyte1;
	int		Gbyte1;
	int		Bbyte1;
	int		Rbyte2;
	int		Gbyte2;
	int		Bbyte2;
	int		flag;
	float	h;
	float	w;
}	t_vls;

void			init_data(t_struct_data	*data);

int				keyboard(int keycode, t_vars *vars);

void			drawLine(t_vls xyz, t_data *img, t_struct_data *map);

int				grad_col(t_struct_data *map, t_line line, t_vls *xyz);

unsigned int	ft_ahextoi(const char *str);

char			*reader(int fd);

t_struct		**map_struct(char **split, t_struct_data *data);

void			mlx_line(t_struct_data *map, t_data	*img);

#endif