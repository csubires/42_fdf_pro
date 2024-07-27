/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:06:43 by csubires          #+#    #+#             */
/*   Updated: 2024/07/27 11:46:47 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_map(t_map *map)
{
	int32_t	x;

	if (!map)
		return ;
	if (map->z_gen)
	{
		x = -1;
		while (++x < map->height)
			if (map->z_gen[x])
				free(map->z_gen[x]);
		free(map->z_gen);
	}
	if (map->color_file)
	{
		x = -1;
		while (++x < map->height)
			if (map->color_file[x])
				free(map->color_file[x]);
		free(map->color_file);
	}
	free(map);
}

void	set_z_limits(t_map *map)
{
	int32_t	x;
	int32_t	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->z_gen[y][x] < map->min_z)
				map->min_z = map->z_gen[y][x];
			else if (map->z_gen[y][x] > map->max_z)
				map->max_z = map->z_gen[y][x];
		}
	}
}

void	create_struct_mem(t_map *map)
{
	int32_t	x;

	map->z_gen = (int32_t **)malloc(sizeof(int32_t *) * map->height);
	map->color_file = (int32_t **)malloc(sizeof(int32_t *) * map->height);
	if (!map->z_gen || !map->color_file)
	{
		free_map(map);
		error_and_exit("create_struct_mem", "malloc Pt1");
	}
	x = -1;
	while (++x < map->height)
	{
		map->z_gen[x] = (int32_t *)malloc(sizeof(int32_t) * map->width);
		map->color_file[x] = (int32_t *)malloc(sizeof(int32_t) * map->width);
		if (!map->z_gen[x] || !map->color_file[x])
		{
			free_map(map);
			error_and_exit("create_struct_mem", "malloc Pt2");
		}
	}
}

static int32_t	get_width(t_map *map, char *line)
{
	int32_t		width;
	char	**split;

	if (!line)
		return (0);
	split = ft_split(line, ' ');
	if (!split)
	{
		free_map(map);
		error_and_exit("get_width", "split = ft_split");
	}
	width = 0;
	while (split[width])
		width++;
	ft_free_split(split);
	return (width);
}

t_map	*initialise_map(char *file)
{
	int		fd;
	t_map	*map;
	char	*line;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		error_and_exit(file, "Error to open file");
	}
	line = ft_get_next_line(fd);
	map->width = get_width(map, line);
	while (line)
	{
		map->height++;
		free(line);
		line = ft_get_next_line(fd);
	}
	free(line);
	close(fd);
	return (map);
}
