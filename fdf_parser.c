/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:21:39 by aarchiba          #+#    #+#             */
/*   Updated: 2021/12/03 17:24:07 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*analys_reader(char *c, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(str, c);
	if (!tmp)
		return (NULL);
	if (str)
		free (str);
	return (tmp);
}

static void	map_def(t_struct *map, char **tmp)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (tmp && tmp[j])
	{
		map[j].value = ft_atoi(tmp[j], &flag);
		map[j].color = STD_COLOR;
		if (flag)
			map[j].color = ft_ahextoi((tmp[j] + (flag + 3)));
		free(tmp[j]);
		j++;
		flag = 0;
	}
	free (tmp);
}

static t_struct	**map_creator(t_struct **map, char **split, t_struct_data *data)
{
	int		j;
	int		i;
	char	**tmp;

	i = 0;
	while (split[i])
	{
		j = 0;
		tmp = ft_split(split[i], ' ');
		while (tmp[j])
			j++;
		data->width = j;
		map[i] = malloc(sizeof(t_struct) * j);
		if (!(map[i]))
		{
			free (tmp);
			free (split[i]);
			return (NULL);
		}
		map_def(map[i], tmp);
		free (split[i]);
		i++;
	}
	return (map);
}

t_struct	**map_struct(char **split, t_struct_data *data)
{
	int			i;
	char		**tmp;
	t_struct	**map;

	i = 0;
	tmp = split;
	while (tmp[i])
		i++;
	data->height = i;
	map = malloc(sizeof(t_struct *) * i);
	if (!map)
		return (NULL);
	map = map_creator(map, split, data);
	free(tmp);
	return (map);
}

char	*reader(int fd)
{
	char	*str;
	int		i;
	char	c[BUF_SIZE + 1];

	str = malloc(1);
	if (str)
	{
		str[0] = 0;
		while (1)
		{
			i = read(fd, c, BUF_SIZE);
			if (i < 0)
				break ;
			else if (!i)
				return (str);
			c[i] = '\0';
			str = analys_reader(c, str);
			if (!str)
				break ;
		}
		free (str);
	}
	return (NULL);
}
